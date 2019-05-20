//
// Created by natalia on 14/05/19.
//
#include "pzcmesh.h"
#include "TPZPlasticStepPV.h"
#include "TPZYCMohrCoulombPV.h"
#include "TPZElastoPlasticMem.h"
#include "TPZMatElastoPlastic2D.h"

#ifndef INTPOINTSFEM_TPZIRREGULARBLOCKMATRIX_H
#define INTPOINTSFEM_TPZIRREGULARBLOCKMATRIX_H


class TPZIrregularBlockMatrix {
public:
    /** @brief Default constructor */
    TPZIrregularBlockMatrix();

    /** @brief Creates the object based on cmesh
     * @param cmesh : computational mesh
     */
    TPZIrregularBlockMatrix(TPZCompMesh *cmesh, int materialid);

    /** @brief Default destructor */
    ~TPZIrregularBlockMatrix();

    /** @brief Creates a irregular block matrix with copy constructor
     * @param copy : original irregular block matrix
     */
    TPZIrregularBlockMatrix(const TPZIrregularBlockMatrix &copy);

    /** @brief operator= */
    TPZIrregularBlockMatrix &operator=(const TPZIrregularBlockMatrix &copy);

    /** @brief Sets the computational mesh
     * @param cmesh : computational mesh
     */
    void SetCompMesh(TPZCompMesh *cmesh) {
        fCmesh = cmesh;
    }

    /** @brief Sets the material id
     * @param materialid : material id
     */
    void SetMaterialId (int materialid) {
        TPZMaterial *material = fCmesh->FindMaterial(materialid);
        fMaterial = dynamic_cast<TPZMatElastoPlastic2D<TPZPlasticStepPV<TPZYCMohrCoulombPV,TPZElasticResponse> , TPZElastoPlasticMem> *>(material);
    }

    /** @brief Sets blocks information */
    void BlocksInfo();

    /** @brief Sets blocks information for CSR format*/
    void CSRInfo();

    /** @brief Performs the following operation: res = alpha * BMatrix * A + beta * res
     * @param A : matrix that will be multipied
     * @param res : result of the multiplication
     * @param alpha : scalar parameter
     * @param beta : scalar parameter
     * @param opt : indicates if transpose or not
     */
    void Multiply(TPZFMatrix<REAL> &A, TPZFMatrix<REAL> &res, REAL alpha, REAL beta, bool transpose = false);

    /** @brief Access methods */

    int Dimension() {
        return fDim;
    }

    TPZCompMesh *CompMesh() {
        return fCmesh;
    }

    TPZMatElastoPlastic2D<TPZPlasticStepPV<TPZYCMohrCoulombPV,TPZElasticResponse>, TPZElastoPlasticMem> *Material() {
        return fMaterial;
    }

    int64_t NumBlocks() {
        return fNumBlocks;
    }

    TPZVec<REAL> Storage() {
        return fStorage;
    }

    TPZVec<int> RowSizes() {
        return fRowSizes;
    }

    TPZVec<int> ColSizes() {
        return fColSizes;
    }

    TPZVec<int> MatrixPosition() {
        return fMatrixPosition;
    }

    TPZVec<int> RowFirstIndex() {
        return fRowFirstIndex;
    }

    TPZVec<int> ColFirstIndex() {
        return fColFirstIndex;
    }

    int Rows() {
        return fRow;
    }

    int Cols() {
        return fCol;
    }

    TPZVec<int> RowPtr() {
        return fRowPtr;
    }

    TPZVec<int> ColInd() {
        return fColInd;
    }

    TPZStack<int64_t> ElemIndexes() {
        return fElemIndex;
    }

    TPZStack<int64_t> BoundaryElemIndexes() {
        return fBoundaryElemIndex;
    }

private:
    /** @brief Mesh Dimension */
    int fDim;

    /** @brief Computational mesh */
    TPZCompMesh *fCmesh;

    /** @brief Material */
    TPZMatElastoPlastic2D<TPZPlasticStepPV<TPZYCMohrCoulombPV,TPZElasticResponse>, TPZElastoPlasticMem> *fMaterial;

    /** @brief Number of blocks */
    int64_t fNumBlocks;

    /** @brief Vector of all matrices values */
    TPZVec<REAL> fStorage;

    /** @brief Vector of number of rows of each matrix */
    TPZVec<int> fRowSizes;

    /** @brief Vector of number of columns of each matrix */
    TPZVec<int> fColSizes;

    /** @brief Vector of matrix position in fStorage */
    TPZVec<int> fMatrixPosition;

    /** @brief Vector of first row index of each matrix */
    TPZVec<int> fRowFirstIndex;

    /** @brief Vector of first column index of each matrix */
    TPZVec<int> fColFirstIndex;

    /** @brief Number of rows of the irregular block matrix */
    int64_t fRow;

    /** @brief Number of columns of the irregular block matrix */
    int64_t fCol;

    /** @brief Vector of the start of every row and the end of the last row plus one (this is for CSR format) */
    TPZVec<int> fRowPtr;

    /** @brief Vector of column indices for each non-zero element of the matrix (this is for CSR format)*/
    TPZVec<int> fColInd;

    /** @brief Vector of indexes of the domain elements*/
    TPZStack<int64_t> fElemIndex;

    /** @brief Vector of indexes of the boundary elements*/
    TPZStack<int64_t> fBoundaryElemIndex;
};


#endif //INTPOINTSFEM_TPZIRREGULARBLOCKMATRIX_H