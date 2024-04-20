#include "Database.h"


using namespace config4cpp;
using namespace std;

int parseConfig() {
  Configuration *cfg = Configuration::create();
  const char *scope = "";
  const char *configFile = "someFile.cfg";
  const char *url;
  const char *file;
  bool true_false;

  try {
    cfg->parse(configFile);
    url = cfg->lookupString(scope, "url");
    file = cfg->lookupString(scope, "file");
    true_false = cfg->lookupBoolean(scope, "true_false");
  } catch (const ConfigurationException &ex) {
    cerr << ex.c_str() << endl;
    cfg->destroy();
    return 1;
  }
  cout << "url=" << url << "; file=" << file
       << "; true_false=" << true_false
       << endl;
  cfg->destroy();
  return 0;
}