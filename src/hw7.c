//Tyler Saint Joy
//116189402
#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    //bbase case
    if(root == NULL){
        bst_sf *newNode = malloc (sizeof(bst_sf));
        newNode -> mat = mat;
        newNode -> left_child = NULL;
        newNode -> right_child = NULL;
        return newNode;
    }
    //recursive case
    if(mat -> name < root -> mat -> name){
        root -> left_child = insert_bst_sf(mat, root -> left_child);
    } 
    else{
        root -> right_child = insert_bst_sf(mat, root -> right_child);
    }
    return root; 
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    //base case
    if(root == NULL){
        return NULL;
    }
    if(name == root -> mat -> name){
        return root -> mat;
    }   
    if(name < root -> mat -> name){
        return find_bst_sf(name, root -> left_child);
    }
    else{
        return find_bst_sf(name, root -> right_child);
    }

}

void free_bst_sf(bst_sf *root) {
    if(root == NULL){
        return;
    }
    //free children then free self for postorder
    free_bst_sf(root -> left_child);
    free_bst_sf(root -> right_child);
    free(root -> mat);
    free(root);
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    //allocating memory for matrix of result values
    matrix_sf *result = malloc(sizeof(matrix_sf) + mat1 -> num_rows * mat1 -> num_cols * sizeof(int)); 
    //create dimensions the same as mat1 
    result -> name = '/0';
    result -> num_rows = mat1 -> num_rows;
    result -> num_cols = mat1 -> num_cols;
    //iterate through matrices, add the values and store the sum in result
    for(int i = 0; i < ((mat1 -> num_rows)*(mat1 -> num_cols)); i++){
        result -> values[i] = mat1 -> values[i] + mat2 -> values[i]; 
    }
    return result; 
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    //allocating memory for matrix of result values, result is mat1 rows x mat2 cols
   matrix_sf *result = malloc(sizeof(matrix_sf) + mat1 -> num_rows * mat2 -> num_cols * sizeof(int));
   //mat1 rows x mat2 cols
   result -> name = '/0';
   result -> num_rows = mat1 -> num_rows;
   result -> num_cols = mat2 -> num_cols;

   for(int i = 0; i < mat1 -> num_rows; i++){
    for(int j = 0; j < mat2 -> num_cols; j++){
        int tempSum = 0;
        for(int k = 0; k < mat1 -> num_rows; k++){
            //m1[i][k] * m2[k][j]
            tempSum += mat1 -> values[i * mat1 -> num_cols + k] * mat2 -> values[k * mat2 -> num_cols + j]; 
        }
        //store [i][j]
        result -> values[i * mat2 -> num_cols + j] = tempSum; 
    }

   }
   return result; 

}   

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    matrix_sf *result = malloc(sizeof(matrix_sf) + mat -> num_cols * mat -> num_rows * sizeof(int));
    result -> name = '/0';
    result -> num_rows = mat -> num_cols;
    result -> num_cols = mat -> num_rows;
    //result[j][i] = mat[i][j]
    for(int i = 0; i < mat -> num_rows; i++){
        for(int j = 0; j < mat -> num_cols; j++){
            result -> values[j * result -> num_cols + i] = mat -> values[i * mat -> num_cols + j];
        }
    }
    return result;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    int rows, cols;
    const char *ptr = expr;
    //get rows
    while(*ptr == ' ') ptr++; 
    rows = 0; 
    while(*ptr >= '0' && *ptr <= '9'){
        rows = rows * 10 + (*ptr - '0');
        ptr++;
    }
    //get cols
    while(*ptr == ' ') ptr++;
    cols = 0;
    while(*ptr >= '0' && *ptr <= '9'){
        cols = cols * 10 + (*ptr - '0');
        ptr++;
    }
    
    matrix_sf *newMatrix = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    newMatrix -> name = name;
    newMatrix -> num_rows = rows;
    newMatrix -> num_cols = cols;

    while(*ptr != '[') ptr++; //go to the first [
    ptr++; //move past [
    
    int index = 0;
    //skip past spaces and semicolons
    while(*ptr != ']'){
        while(*ptr == ' ' || *ptr == ';'){
            ptr++;
        }
        if(*ptr == ']'){
            break;
        }
        int value = 0;
        int sign = 1;
        if(*ptr == '-'){
            sign = 0;
            ptr++;
        }
        while(*ptr >= '0' && *ptr <= '9'){
            value = value * 10 + (*ptr - '0');
            ptr++;
        }
        if(sign == 0){
            value = -value;
        }
        newMatrix -> values[index] = value;
        index++;
    }
    return newMatrix;   
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
