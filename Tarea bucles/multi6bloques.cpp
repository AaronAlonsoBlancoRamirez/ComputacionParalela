#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<int>> generate_matrix(int rows, int cols) {
    srand(time(NULL)); // Inicializar semilla de números aleatorios
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10; // Generar números aleatorios entre 0 y 9
        }
    }
    return matrix;
}

vector<vector<int>> mult_matrices(vector<vector<int>> A, vector<vector<int>> B) {
    // Asegurarse de que las matrices son multiplicables
    if (A[0].size() != B.size()) {
        throw "Las matrices no son multiplicables";
    }

    int n = A.size();
    int m = B.size();
    int p = B[0].size();

    vector<vector<int>> C(n, vector<int>(p, 0));

    // Multiplicación de matrices por 6 bloques anidados
    int block_size = 16;
    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < p; j += block_size) {
            for (int k = 0; k < m; k += block_size) {
                for (int ii = i; ii < min(i + block_size, n); ii++) {
                    for (int jj = j; jj < min(j + block_size, p); jj++) {
                        for (int kk = k; kk < min(k + block_size, m); kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }

    return C;
}

int main() {
    // Ejemplo de multiplicación de matrices
    int z = 1000; // Tamaño de las matrices
    vector<vector<int>> A = generate_matrix(z, z);
    vector<vector<int>> B = generate_matrix(z, z);
    unsigned t0, t1;
 
    t0=clock();
    vector<vector<int>> C = mult_matrices(A, B);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "T: " << time << endl;

    // Imprimir las matrices
    /*cout << "Matriz A:" << endl;
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < z; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz B:" << endl;
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < z; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matriz C = A x B:" << endl;
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < z; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }*/

    return 0;
}