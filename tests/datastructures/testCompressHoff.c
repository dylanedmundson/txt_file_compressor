#include "datastructures/compressHoff.h"
#include "testUtils.h"


testPass testBuildFreqList() {
    /* test empty text */
    FILE *emptyFile = fopen("C:\\Users\\dylan\\VsCodeRepos\\txt_file_compressor\\tests\\testRes\\emptyTest.txt", "r");
    mPriorityQueue *pqEmpty = buildFreqList(emptyFile);
    ASSERT_EQUALS(pqEmpty->size, 0)
    fclose(emptyFile);
    free(emptyFile);
    free(pqEmpty);

    /* test signleTest */
    FILE *singleFile = fopen("C:\\Users\\dylan\\VsCodeRepos\\txt_file_compressor\\tests\\testRes\\singleTest.txt", "r");
    mPriorityQueue *pqSingle = buildFreqList(singleFile);
    tNode *val = pop(pqSingle);
    ASSERT_EQUALS(val->c, 'a')
    ASSERT_EQUALS(val->freq, 1)
    fclose(singleFile);
    free(singleFile);
    free(pqSingle);

    /* test small */
    FILE *testSmall = fopen("C:\\Users\\dylan\\VsCodeRepos\\txt_file_compressor\\tests\\testRes\\smallTest.txt", "r");
    mPriorityQueue *pqSmall = buildFreqList(testSmall);
    val = pop(pqSmall);
    ASSERT_EQUALS(val->freq, 3)
    val = pop(pqSmall);
    ASSERT_EQUALS(val->freq, 3)
    val = pop(pqSmall);
    ASSERT_EQUALS(val->c, 'b')
    ASSERT_EQUALS(val->freq, 4)
    val = pop(pqSmall);
    ASSERT_EQUALS(val->c, 'c')
    ASSERT_EQUALS(val->freq, 5)
    fclose(testSmall);
    free(testSmall);
    free(val);
    free(pqSmall);
    return PASS;
}

int main() {
    ASSERT_PASS_TEST(testBuildFreqList())
}