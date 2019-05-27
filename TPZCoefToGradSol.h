//
// Created by natalia on 24/05/19.
//

#include "TPZIrregularBlocksMatrix.h"

#ifdef USING_MKL
#include <mkl.h>
#endif

#ifndef INTPOINTSFEM_TPZCOEFTOGRADSOL_H
#define INTPOINTSFEM_TPZCOEFTOGRADSOL_H


class TPZCoefToGradSol {

public:
    TPZCoefToGradSol();

    TPZCoefToGradSol(TPZIrregularBlocksMatrix irregularBlocksMatrix);

    ~TPZCoefToGradSol();

    void SetIrregularBlocksMatrix(TPZIrregularBlocksMatrix irregularBlocksMatrix);

    void CoefToGradU(TPZFMatrix<REAL> &coef, TPZFMatrix<REAL> &grad_u);

    void SigmaToRes(TPZFMatrix<REAL> &sigma, TPZFMatrix<REAL> &res);

    void SetIndexes(TPZVec<int> indexes) {
        fIndexes = indexes;
    }

    void SetIndexesColor(TPZVec<int> indexescolor) {
        fIndexesColor = indexescolor;
    }

    void SetNColors(int ncolor) {
        fNColor = ncolor;
    }


private:
    TPZIrregularBlocksMatrix fBlockMatrix;

    int64_t fNColor;

    TPZVec<int> fIndexes;

    TPZVec<int> fIndexesColor;

};


#endif //INTPOINTSFEM_TPZCOEFTOGRADSOL_H
