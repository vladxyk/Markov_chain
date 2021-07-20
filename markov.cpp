#include <iostream>
#include <string>
#include "string.h" 

using namespace std;

void mult(float **a, int n, float **res){

/*
    cout << "a" << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
*/
    for (int i = 0; i < n; i++){
        res[i] = new float[n];
        for (int j = 0; j < n; j++){
            res[i][j] = 0;
            for (int k = 0; k < n; k++){
                res[i][j] = res[i][j] + a[i][k] * a[k][j];
            }
        }
    }
        
    for(int i  = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            a[i][j]=res[i][j];
        }
    }
/*
    cout << "Mult matrix" << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
*/
  
}

int main(){
    
    cout << "Enter the number of events: ";
    int n;
    cin >> n;
    cout << endl;

    float** matrix = new float*[n];
    srand(time(NULL));

    float sum;
    cout << "Enter the transition matrix or get a random transition matrix (e/g): ";
    string c;
    cin >> c;
    if(c == "e"){
        for(int i = 0; i < n; i++){
            matrix[i] = new float[n];
            sum = 0;
            for(int j = 0; j < n; j++){
                cin >> matrix[i][j];
                sum = sum + matrix[i][j];
            }
            if(sum < 1 || sum > 1){
                cout << "Error: sum of the elements of the row must be equal to 1" << endl;
                return -1;
            }
        }
    }

    else if(c == "g"){
        for(int i = 0; i < n; i++){
            matrix[i] = new float[n];
            sum = 0;
            for(int j = 0; j < n; j++){
                matrix[i][j] = rand()%101;
                matrix[i][j] = matrix[i][j] / 100;
                if(i != j){
                    sum = sum + matrix[i][j];
                }
            }
            if(sum < 1){
                matrix[i][i] = 1 - sum;
            }
            else if(sum == 1){
                matrix[i][i] = 0;
            }
            else if(sum > 1){
                for(int j = 0; j < n; j++){
                    matrix[i][j] = 0;
                }
                int j = rand()%n;
                matrix[i][j] = 1;
            }
        }
    }
    else{
        cout << "Error: enter e/g" << endl;
        return -1;
    }
    
    cout << endl << "Transition matrix: " << endl;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
/*
    float k;
    k = matrix[0][0];
    int events;
    int t = 0;
    
    while(t<10){
        for(int i = 0; i < n; i++){
            cout << "verhina " << i + 1 << endl;
            for(int j = 0; j < n; j++){
                events = rand()%n;
                k = matrix[i][events];
                cout << "events = " << events << " k = " << k << " ";
            }
        cout << endl;
        }
        cout << endl;
        t++;
    }
*/
    cout << endl;
    cout << "If you want to get the probability from one state to another, enter 1" << endl;
    cout << "If you want to get this probability in a few steps, enter 2" << endl;

    int choice;
    cin >> choice;

    if(choice == 1){
        float *vector = new float[n];
        float tmp;
        float *res_vector = new float[n];
        sum = 0;

        cout << endl <<"Enter initial state vector: ";
        for(int i = 0; i < n; i++){
            cin >> vector[i];
            sum = sum + vector[i];
        }

        if(sum < 1 || sum > 1){
            cout << "Error: sum of the elements must be equal to 1" << endl;
            return -1;
        }
/*
        cout << endl << "Initial state vector: " << endl;
        for(int i = 0; i < n; i++){
            cout << vector[i] << " ";
        }
*/
        for(int i = 0; i < n; i++){
            tmp = 0;
            for(int j = 0; j < n; j++){
                tmp = tmp + matrix[i][j] * vector[j];
            }
            res_vector[i] = tmp;
        }

        cout << endl << "Result vector: " << endl;
        for(int i = 0; i < n; i++){
            cout << res_vector[i] << " ";
        }
        cout << endl;

        delete[] vector;
        delete[] res_vector;
    }
    else if(choice == 2){
        cout << endl << "Enter the number of steps: ";
        int steps;
        cin >> steps;
        int tsteps = steps;
        float **res = new float*[n];
        
        while(tsteps > 1){
            mult(matrix, n, res);
            tsteps--;
        }
        
        cout << endl << "Transition matrix in "<< steps << " steps" << endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
        delete[] res;
    }


    cout << endl;

    delete[] matrix;
    return 0;

}
