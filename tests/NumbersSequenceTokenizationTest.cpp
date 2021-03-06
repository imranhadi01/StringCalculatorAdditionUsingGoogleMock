#include <gmock\gmock.h>

#include "..\code\NumbersSequenceTokenizer.h"
#include "..\code\DelimitersExtractor.h"

using namespace ::testing;

class ANumbersExtractor : public Test {
public:
  NumbersSequenceTokenizer * numbersSequenceTokenizer;

  void SetUp() {
    std::vector<std::string> DefaultDelimiters = {",", "\n"};
    numbersSequenceTokenizer = new NumbersSequenceTokenizer(
      new DelimitersExtractor(DefaultDelimiters));
  }

  void TearDown() {
    delete numbersSequenceTokenizer;
  }
};

TEST_F(ANumbersExtractor, ReturnsEmptyListWhenItReceivesAnEmptySequence) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom(""), IsEmpty());
}

TEST_F(ANumbersExtractor, ReturnsTheOnlyNumberInSequence) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom("5"), ElementsAre(5));
}

TEST_F(ANumbersExtractor, ExtractsNumbersSeparatedByCommas) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom("3, 4, 6"), ElementsAre(3, 4, 6));
}

TEST_F(ANumbersExtractor, ExtractsNumbersSeparatedByCommasOrNewLineCharacters) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom("1\n2, 3"), ElementsAre(1, 2, 3));
}

TEST_F(ANumbersExtractor, ExtractsNumbersSeparatedByAdditionalDelimitersWithOneCharacter) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom("//[@]\n1@2"), ElementsAre(1, 2));
}

TEST_F(ANumbersExtractor, ExtractsNumbersSeparatedByAdditionalDelimitersWithSeveralCharacters) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom("//[;;]\n1;;2"), ElementsAre(1, 2));
}

TEST_F(ANumbersExtractor, ExtractsNumbersSeparatedByAdditionalDelimitersUsedInRegularExpressions) {
  ASSERT_THAT(numbersSequenceTokenizer->extractFrom("//[*]\n1*2"), ElementsAre(1, 2));
}