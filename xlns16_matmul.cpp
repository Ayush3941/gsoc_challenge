// Matrix multiply using 16-bit XLNS (alt path)
#include <stdio.h>
#include <vector>

#define xlns16_alt
#define xlns16_altopt
#include "extern/xlnscpp/xlns16.cpp"

using namespace std;

static vector<vector<xlns16>> read_matrix16(int rows, int cols) {
    vector<vector<xlns16>> m(rows, vector<xlns16>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float v;
            printf("Enter value for %dth Column of %d Row\n", j + 1, i + 1);
            scanf("%f", &v);
            m[i][j] = fp2xlns16(v);
        }
    }
    return m;
}

static vector<vector<xlns16>> matmul16(const vector<vector<xlns16>> &a,const vector<vector<xlns16>> &b,int r1, int c1, int c2) {
    vector<vector<xlns16>> out(r1, vector<xlns16>(c2, xlns16_zero));
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            xlns16 sum = xlns16_zero;
            for (int k = 0; k < c1; ++k) {
                sum = xlns16_add(sum, xlns16_mul(a[i][k], b[k][j]));
            }
            out[i][j] = sum;
        }
    }
    return out;
}

int main(void) {
    int rows1, cols1;
    printf("Enter the no. of Rows for 1st Matrix");
    scanf("%d", &rows1);
    printf("Enter the no. of Cols for 1st Matrix");
    scanf("%d", &cols1);
    auto mat1 = read_matrix16(rows1, cols1);

    printf("\n\n\n");
    int rows2, cols2;
    printf("Enter the no. of Rows for 2nd Matrix");
    scanf("%d", &rows2);
    printf("Enter the no. of Cols for 2nd Matrix");
    scanf("%d", &cols2);
    auto mat2 = read_matrix16(rows2, cols2);

    if (cols1 != rows2) {
        printf("For two matrix to multiply the cols of Mat1 should be equal to rows of Mat2");
        return 1;
    }

    auto result = matmul16(mat1, mat2, rows1, cols1, cols2);

    for (int i = 0; i < rows1; ++i) {
        printf("|");
        for (int j = 0; j < cols2; ++j) {
            printf("%f ", xlns162fp(result[i][j]));
        }
        printf("|\n");
    }

    return 0;
}
