//
// Created by natalia on 24/05/19.
//

#include "TPZIrregularBlocksMatrix.h"
#include "TPZConstitutiveLawProcessor.h"

#ifdef USING_CUDA
#include "TPZVecGPU.h"
#include "TPZCudaCalls.h"
#endif


#ifdef USING_MKL
#include <mkl.h>
#endif

#ifndef INTPOINTSFEM_TPZNUMERICALINTEGRATOR_H
#define INTPOINTSFEM_TPZNUMERICALINTEGRATOR_H


class TPZNumericalIntegrator {

public:

    TPZNumericalIntegrator();

    TPZNumericalIntegrator(TPZIrregularBlocksMatrix &irregularBlocksMatrix);

    ~TPZNumericalIntegrator();

    void Multiply(TPZFMatrix<REAL> &coef, TPZFMatrix<REAL> &delta_strain);

    void MultiplyTranspose(TPZFMatrix<REAL> &sigma, TPZFMatrix<REAL> &res);

    void ResidualIntegration(TPZFMatrix<REAL> & solution ,TPZFMatrix<REAL> &rhs);

    void ComputeConstitutiveMatrix(int64_t point_index, TPZFMatrix<STATE> &De);

    void ComputeTangentMatrix(int64_t iel, TPZFMatrix<REAL> &Dep, TPZFMatrix<REAL> &K);

    void ComputeTangentMatrix(int64_t iel, TPZFMatrix<REAL> &K);

    void SetUpIrregularBlocksData(TPZCompMesh * cmesh);

    int StressRateVectorSize(int dim);

    void SetUpIndexes(TPZCompMesh * cmesh);

    void SetUpColoredIndexes(TPZCompMesh * cmesh);

    void FillLIndexes(TPZVec<int64_t> & IA, TPZVec<int64_t> & JA);

    int64_t me(TPZVec<int64_t> &IA, TPZVec<int64_t> &JA, int64_t & i_dest, int64_t & j_dest);

    bool isBuilt() {
        if(fBlockMatrix.Rows() != 0) return true;
        else return false;
    }

    void KAssembly(TPZFMatrix<REAL> & solution, TPZVec<STATE> & Kg, TPZFMatrix<STATE> & rhs);

#ifdef USING_CUDA
    void Multiply(TPZVecGPU<REAL> &coef, TPZVecGPU<REAL> &delta_strain);
    
    void MultiplyTranspose(TPZVecGPU<REAL> &sigma, TPZVecGPU<REAL> &res); 

    void ResidualIntegration(TPZFMatrix<REAL> & solution ,TPZVecGPU<REAL> &rhs);

    void KAssembly(TPZFMatrix<REAL> & solution, TPZVecGPU<STATE> & Kg, TPZVecGPU<STATE> & rhs);
#endif

    void SetElementIndexes(TPZVec<int> & elemindex) {
        fElementIndex = elemindex;
    }

    TPZVec<int> & ElementIndexes() {
        return fElementIndex;
    }

    void SetIrregularBlocksMatrix(TPZIrregularBlocksMatrix & irregularBlocksMatrix) {
        fBlockMatrix = irregularBlocksMatrix;
    }

    TPZIrregularBlocksMatrix & IrregularBlocksMatrix() {
        return fBlockMatrix;
    }

    void SetConstitutiveLawProcessor(TPZConstitutiveLawProcessor & processor){
        fConstitutiveLawProcessor = processor;
    }

    TPZConstitutiveLawProcessor & ConstitutiveLawProcessor(){
        return fConstitutiveLawProcessor;
    }

    void SetDoFIndexes(TPZVec<int> dof_indexes) {
        fDoFIndexes = dof_indexes;
    }

    TPZVec<int> & DoFIndexes() {
        return fDoFIndexes;
    }

    void SetColorIndexes(TPZVec<int> color_indexes) {
        fColorIndexes = color_indexes;
    }
    
    TPZVec<int> & ColorIndexes() {
     return fColorIndexes;
    }

    void SetNColors(int ncolor) {
        fNColor = ncolor;
    }

    int NColors() {
        return fNColor;
    }

    void SetElColorIndex(TPZVec<int64_t> &el_color_indexes){
        fElColorIndex = el_color_indexes;
    }

    TPZVec<int64_t> &ElColorIndex() {
        return fElColorIndex;
    }

    void SetFirstColorIndex(TPZVec<int64_t> &first_color_index){
        fFirstColorIndex = first_color_index;
    }

    TPZVec<int64_t> &FirstColorIndex() {
        return fFirstColorIndex;
    }

    void SetColorLSequence(TPZVec<int> &color_l_sequence){
        fColorLSequence = color_l_sequence;
    }

    TPZVec<int> &ColorLSequence() {
        return fColorLSequence;
    }

    void SetFirstColorLIndex(TPZVec<int> &first_color_l_index){
        fFirstColorLIndex = first_color_l_index;
    }

    TPZVec<int> &FirstColorLIndex() {
        return fFirstColorLIndex;
    }

#ifdef USING_CUDA
    TPZVecGPU<int> & DoFIndexesDev() {
        return dDoFIndexes;
    }

    TPZVecGPU<int> & ColorIndexesDev() {
        return dColorIndexes;
    }

    TPZVecGPU<int64_t> & ElColorIndexDev() {
        return dElColorIndex;
    }

    TPZVecGPU<int> &ColorLSequenceDev() {
        return dColorLSequence;
    }

    void TransferDataToGPU();

#endif

private:

    TPZVec<int> fElementIndex;

    /// Irregular block matrix containing spatial gradients for scalar basis functions of order k
    TPZIrregularBlocksMatrix fBlockMatrix;

    /// Number of colors grouping no adjacent elements
    int64_t fNColor; //needed to do the assembly

    /// Degree of Freedom indexes organized element by element with stride ndof
    TPZVec<int> fDoFIndexes; // needed to do the gather operation

    /// Color indexes organized element by element with stride ndof
    TPZVec<int> fColorIndexes; //nedeed to scatter operation

    TPZConstitutiveLawProcessor fConstitutiveLawProcessor;

    TPZVec<int64_t> fElColorIndex;

    TPZVec<int64_t> fFirstColorIndex;

    TPZVec<int> fColorLSequence;

    TPZVec<int> fFirstColorLIndex;
    
#ifdef USING_CUDA
    TPZVecGPU<int> dDoFIndexes;
    TPZVecGPU<int> dColorIndexes;
    TPZCudaCalls fCudaCalls;

    TPZVecGPU<int64_t> dElColorIndex;
    TPZVecGPU<int> dColorLSequence;
#endif


};


#endif //INTPOINTSFEM_TPZNUMERICALINTEGRATOR_H
