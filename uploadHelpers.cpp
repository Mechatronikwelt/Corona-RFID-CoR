#include "uploadHelpers.h"

String createURL(PersonData pushData, const char* key) {
  String URL="https://script.google.com/macros/s/"; 
  URL += key;
  URL += "/exec?";
  URL += "1="+pushData.Name;
  URL += "&2="+pushData.Organisation;
  URL += "&3="+pushData.Address;
  URL += "&4="+(String)pushData.Number;
  URL += "&5="+(String)pushData.Intent;
  return URL;
}
