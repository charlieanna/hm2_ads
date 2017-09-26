//HW2: Sparse Matrix Operation -- Applicaiton of 2-D linked lists
//by C-Y (Roger) Chen
//Due:  11:59pm, Wed. September 27
//Implement the following three member functions for the class my_matrix:
//add_node, operator+, operator*
//Do not change the main function and the my_matrix::print function

#include <iostream>
#include <vector>
using namespace std;

class node {
public:
    int value;
    int r_position;
    int c_position;
    node * r_next;
    node * c_next;
    node() { value = -9999; r_position = c_position = -1; r_next = c_next = nullptr; }
    node(int v, int r, int c) { value = v; r_position = r; c_position = c; r_next = c_next = nullptr; }

};
class my_matrix {
public:
    int num_rows;
    int num_cols;
    vector<node *> r_vec;
    vector<node *> c_vec;


    my_matrix(){}
    my_matrix(int r, int c);
    //Initialize a matrix of rows and c cols.

    my_matrix(int r, int c, int n, int k);
    //Initializa a matrix of r rows, c cols, n nodes, with values randomly in - (k-1) ... (k-1);
    void print(); //print value, r_position, and c_position of all matrix elements in row-oriented manner


    //Implement the following three member functions:

    void add_node(int v, int r, int c);
    //Create a new node with value v at row r and col c.
    //If there already exists an element at this position, then just update the node
    //value at this position to v, and do not create a new node.

    my_matrix operator+(my_matrix M);//matrix addition

    my_matrix operator*(my_matrix M); //matrix multiplication


};

my_matrix  my_matrix::operator*(my_matrix M) {
    // to multiple two matrices who multiple each row node ofmatrix one with each column node of matrix m. For this u will have
    // maintain a column matrix too.
    my_matrix product_matrix(num_rows, M.num_cols);
    for(int i = 0 ; i < num_rows; i++){
        // for each row.
        node *p1 = r_vec.at(i);
        // now multiply each element with a node in the column vector. and sum.
        for(int j = 0; j < M.num_cols; j++){
            node *p2 = M.c_vec.at(j);
            int product = 0;
            while (p1 != nullptr && p2!= nullptr) {
                if(p1->r_next== nullptr && p2->r_next== nullptr){
                    break;
                }
                if(p1->r_next || p2->r_next) {
                    //if positions of both are the same
                    if(p1->r_next && p2->r_next== nullptr){
                        p1 = p1->r_next;
                    }else if(p2->r_next && p1->r_next== nullptr){
                        p2 = p2->r_next;
                    }
                    else if(p1->r_next->c_position == p2->r_next->r_position) {
                        product += p1->r_next->value * p2->r_next->value;
                        p1 = p1->r_next;
                        p2 = p2->r_next;
                    }else if(p1->r_next->c_position < p2->r_next->c_position){
                        p1 = p1->r_next;
                    }else if(p1->r_next->c_position > p2->r_next->c_position){
                        p2 = p2->r_next;
                    }
                    product_matrix.add_node(product, i, j);
                }

            }
        }
        return product_matrix;
    }
}

my_matrix my_matrix::operator+(my_matrix M) {
    //to add two matrices. they will be of equal sizes that is same rows and columns.
    // you also have to create a new matrix.
    // there will be a condition where either of the entries might be zero.
    my_matrix sum_matrix(num_rows, num_cols);
    // first you add this matrix with M then you add M with this matrix.
    for (int i = 0; i < num_rows; i++) {
        node *p1 = r_vec[i];
        node *p2 = M.r_vec[i];
        cout << endl;

        while (p1 != nullptr && p2!= nullptr) {
            if(p1->r_next== nullptr && p2->r_next== nullptr){
                break;
            }
            if(p1->r_next || p2->r_next) {
                //if positions of both are the same
                if(p1->r_next && p2->r_next== nullptr){
                    sum_matrix.add_node(p1->r_next->value, p1->r_next->r_position, p1->r_next->c_position);
                    p1 = p1->r_next;
                }else if(p2->r_next && p1->r_next== nullptr){
                    sum_matrix.add_node(p2->r_next->value, p2->r_next->r_position, p2->r_next->c_position);
                    p2 = p2->r_next;
                }
                else if(p1->r_next->c_position == p2->r_next->c_position) {
                    int sum = p1->r_next->value + p2->r_next->value;
                    sum_matrix.add_node(sum, p1->r_next->r_position, p1->r_next->c_position);
                    p1 = p1->r_next;
                    p2 = p2->r_next;
                }else if(p1->r_next->c_position < p2->r_next->c_position){
                    sum_matrix.add_node(p1->r_next->value, p1->r_next->r_position, p1->r_next->c_position);
                    p1 = p1->r_next;
                }else if(p1->r_next->c_position > p2->r_next->c_position){
                    sum_matrix.add_node(p2->r_next->value, p2->r_next->r_position, p2->r_next->c_position);
                    p2 = p2->r_next;
                }

            }

        }
    }
    return sum_matrix;
}

void my_matrix::add_node(int v, int r, int c) {
    // To handle the case when v == 0
    // maintain a previous pointer to handle this

    // when you add a node, based on the column number get the column vector. as soon as you get a node with same row and
    // column, you point it to the next column node.
    node *new_node = new node(v, r, c);
    // if the vec[r] is null then we need to create one.
    node *p = r_vec.at(r);
    node *column_vec = c_vec.at(c);
    node *previous = nullptr;
    if(v == 0 && p!= nullptr){
        if(p->c_next == nullptr){
            // remove p.
            r_vec[r] = nullptr;
        }
        else {
            while (p->c_next) {
                previous = p;
                p = p->c_next;
                if (r == p->r_position && c == p->c_position) {
                    previous->c_next = p->c_next;
                }
            }
        }
    }
    if (p == nullptr) {
        p = new_node;
        r_vec[r] = p;
    } else {// row pointer has 3 values. first one is the row number, second one points to the next row, 3rd points to the column node.
        while (p != nullptr) {
            node *col = p->r_next;
            if (col == nullptr) {
                p->r_next = new_node;
                break;
            }
            int column = col->c_position;
            // if the column node isnt pointing to anything else than make it point to the new node.
            // if c < column that means we need to add before the first column.
            if (c < column && v != 0) {
                p->r_next = new_node;
                new_node->r_next = col;
                break;
            } else if (c == column) { // column is same as c. just update its value
                col->value = v;
                break;
            } else {
                // go to next if next does exists.
                p = p->r_next;
            }

        }
    }
    // the node has already been added to the row vector. we start transversing the column vector and keep going till we get
    // this vector.
    if (column_vec == nullptr) {
        column_vec = new_node;
        c_vec[c] = column_vec;
    }
    else {
        while (column_vec != nullptr) {
            node *next = column_vec->c_next;
            if (next == nullptr) {
                column_vec->c_next = new_node;
                break;
            }
            int row = column_vec->r_position;
            // if the column node isnt pointing to anything else than make it point to the new node.
            // if c < column that means we need to add before the first column.
            if (r < row) {
                column_vec->c_next = new_node;
                new_node->c_next = next;
                break;
            }  else {
                // go to next if next does exists.
                column_vec = column_vec->c_next;
            }
        }
    }
}




my_matrix::my_matrix(int r, int c) {
    num_rows = r;
    num_cols = c;
    r_vec.resize(r, nullptr);
    c_vec.resize(c, nullptr);
}


my_matrix::my_matrix(int r, int c, int n, int k) {
    num_rows = r;
    num_cols = c;
    r_vec.resize(r, nullptr);
    c_vec.resize(c, nullptr);
    for (int i = 0; i < n; i++) {
        int vv = rand() % (2 * k - 1) - (k - 1);
        int rr = rand() % r;
        int cc = rand() % c;
        add_node(vv, rr, cc);
    }
}



void my_matrix::print() {
    cout << endl;
    for (int i = 0; i < num_rows; i++) {
        node * p = r_vec[i];
        cout << endl;
        while (p != nullptr) {
            cout << p->value << " " << p->r_position << " " << p->c_position << "  ";
            p = p->r_next;
        }
    }
}



int main() {
    my_matrix M1(7, 5, 11, 8), M2(7, 5, 10, 8), M3(7, 5), M4(5, 6, 13, 9), M5(7, 6);
    M1.print();
    cout << endl;
    cout << "....................................";
    cout << endl;
    M2.print();
    cout << "....................................";
    cout << endl;
    M3 = M1 + M2;
    M3.print();
    cout << "....................................";
    cout << endl;
    M1.print();
    cout << "....................................";
    cout << endl;
    M4.print();
    cout << "....................................";
    cout << endl;
    M5 = M1 * M4;
    M5.print();
    cout << endl;
    getchar();
    getchar();
    return 0;
}