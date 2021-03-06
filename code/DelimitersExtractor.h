#pragma once

#include <string>
#include <vector>

class DelimitersExtractor
{
public:
  DelimitersExtractor(const std::vector<std::string> & defaultDelimiters);
  virtual ~DelimitersExtractor();

  std::vector<std::string> extractDelimitersList(
    const std::string & numbersSequence) const;

private:
  std::vector<std::string> defaultDelimiters;

  std::vector<std::string> extractAdditionalDelimiters(
    const std::string & delimitersRegion) const;

  std::string extractDelimitersRegion(const std::string & numbersSequence) const;
};

