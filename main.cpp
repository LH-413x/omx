#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <media/stagefright/foundation/ADebug.h>

#include "OMXHarness.h"

using namespace android;
using namespace std;

/*
int Initialize(int argc, char **argv) {
  if(argc != 2){
    cout << "usage: fuzzer type" << endl; 
    return 0;
  } 
  String8 type(argv[1]);
  h = new FHarness(type);  
  android::ProcessState::self()->startThreadPool();
  return 0;
}

int getFdFromBuffer(size_t size, uint8_t* buffer) {
  string dir_path("/storage/emulated/0/Movies/");
  string file_path=dir_path+string(getpid()); 
  int mFd=open(file_path.string(),O_CREAT | O_RDWR  , 777); 
  if(mFd<0){
    cout << "create file fail" << endl;
    exit(0);
  }
  write(mFd,buffer,size);
  close(mFd);
  mFd=open(file_path.string(),O_RDWR  , 777);
  return mFd;
}
*/

//https://sarcasm.github.io/notes/dev/compilation-database.html#bear-and-intercept-buildi

int main(){
  string component_name("OMX.google.amrnb.decoder");
  string uri("file:///sdcard/media_api/video/H263_500_AMRNB_12.3gp");
  android::ProcessState::self()->startThreadPool();
  sp<Harness> h = new Harness(uri);
  CHECK_EQ(h->initCheck(), (status_t)OK);
  h->test(component_name);
  ALOGI("finish test");
  return 0;
}
