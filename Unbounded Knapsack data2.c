# include <stdio.h>
#include <stdlib.h>

# define c 14
# define n 3
// First row: weights. Second row: Profits
const int weightProfits[2][n] = 
    {{5,6,8},
    {7,6,9}};

int** initialise(){
    int** workingTable = (int**) malloc((c + 1)*sizeof(int*));
    for (int row=0; row < c + 1; row++){
        // always only keep track of 2 columns
        workingTable[row] = (int*) malloc(2*sizeof(int));
        // Leftmost row starts at 0
        workingTable[row][0] = 0;
    }
    workingTable[0][1] = 0;
    return workingTable;
}

void nextRow(int*** workingTablePtr){
    int** workingTable = *workingTablePtr;
    for (int row=0; row < c + 1; row++){
        // move right column to left column
        workingTable[row][0] = workingTable[row][1];
        // set right column to 0
        workingTable[row][1] = 0;
    }
}

void freeTable(int **workingTable){
    for (int row=0; row < c + 1; row++){
        free(workingTable[row]);
    }
    free(workingTable);

}
// colRight refers to working table's right column's index in the imaginary reference column in the canva
void printTable(int **workingTable, int colRight){
    printf("\n\nIteration %d", colRight);
    printf("\nc\\j\t%d\t%d", colRight - 1, colRight);
    printf("\n____________________");
    for (int row=0; row < c + 1; row++){
        printf("\n%d\t%d\t%d", row, workingTable[row][0], workingTable[row][1]);
    }
}

int main() {
    int debug = 0;
    int weight;
    int profit;
    int leftTermProfit;
    int aboveTermProfit;
    int **workingTable = initialise();
    // Take note that this col does not exist in workingTable, but is a useful construct to think about
    // Look at part C: Algorithm of the canva to find out why 
    // canva link: https://www.canva.com/design/DAGjA7i7WwI/wgradV3ZbqXpIJA7Bc-AIA/edit?utm_content=DAGjA7i7WwI&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton
    // Col and row in the code below refers to the imaginary (C+1) by (n+1) table shown in the canva, while workingTable is the thinner table shown to save on space complexity
    for (int col = 1; col<= n; col++){
        // load weight and profit for current column
        weight = weightProfits[0][col -1]; 
        profit = weightProfits[1][col -1]; 
        for (int row = 1; row <= c; row++){

            leftTermProfit = workingTable[row][0];
            if (row - weight < 0) {
                workingTable[row][1] = leftTermProfit;
                continue;
            }
            aboveTermProfit = workingTable[row - weight][1];
            if (debug){
                printf("\nRow number :%d",row);
                printf("\nLeftTermProfit :%d",leftTermProfit);
                printf("\nRightTermProfit :%d",aboveTermProfit);
            }
            workingTable[row][1] = (leftTermProfit > aboveTermProfit + profit)? leftTermProfit : aboveTermProfit + profit;
        }
        printTable(workingTable, col);
        nextRow(&workingTable);
    }
    // The answer is on the bottom right of the imaginary table, so bottom right of the real workingTable
    // But nextRow will transfer this answer to the left row
    printf("\nP(%d) : %d\n", c, workingTable[c][0]);
    freeTable(workingTable);
}