#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <media/stagefright/foundation/ADebug.h>

#include "OMXHarness.h"

using namespace android;
using namespace std;
///sdcard/media_api/video/H263_500_AMRNB_12.3gp
int fuzz();

std::string dir("/sdcard/media_api/video/corpus/");
std::string uri;
std::string path;
std::string type;

extern "C" int LLVMFuzzerInitialize(int* argc, char ***argv) {
  type=string((*argv)[*argc-1]);
  std::cout<< "# of args: " << *argc << "fuzz target:  " << type << std::endl;
  path=dir+type+"/tmper."+type;
  uri="file://"+path;
  *argc=*argc-1;
  return 0;
}


unordered_map<std::string,std::string> typeMapComponentName;

void buildMap(){
  typeMapComponentName[string("3gp")]=string("OMX.google.amrnb.decoder");
  typeMapComponentName[string("aac")]=string("OMX.google.aac.decoder");
  typeMapComponentName[string("flac")]=string("OMX.google.flac.decoder");
  typeMapComponentName[string("opus")]=string("OMX.google.opus.decoder");
  typeMapComponentName[string("g711-alaw")]=string("OMX.google.g711.alaw.decoder");
  typeMapComponentName[string("g711-mlaw")]=string("OMX.google.g711.mlaw.decoder");
  typeMapComponentName[string("ogg")]=string("OMX.google.vorbis.decoder");
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  buildMap();
  std::cout << "create file "<<path<<std::endl;
  int fd=open(path.data(),O_CREAT | O_RDWR  , 777);
  write(fd,data,size);
  close(fd);
  fuzz();
  return 0;
}


int fuzz(){
  string component_name=typeMapComponentName[type];
  std::cout <<"component name:" <<  component_name << std::endl;
  //string uri("file:///sdcard/media_api/video/corpus/3gp/tmper.3gp");
  android::ProcessState::self()->startThreadPool();
  sp<Harness> h = new Harness(uri);
  CHECK_EQ(h->initCheck(), (status_t)OK);
  h->test(component_name);
  ALOGI("finish test");
  return 0;
}
