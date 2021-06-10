#include<iostream>

///****************************************************************************************************
//通过单例模式来实现多index共享gpu资源
class gpuResource {
private:
  // static gpuResource* instance;
  gpuResource();
  gpuResource(const gpuResource &);
  gpuResource &operator=(const gpuResource &);

public:
  faiss::gpu::StandardGpuResources *res;
  static gpuResource *getInstance();
  ~gpuResource();
};
///****************************************************************************************************

///***************************************************************************************
// faiss::gpu::StandardGpuResources* gpuResource::res = NULL;
gpuResource::gpuResource() {
  res = new faiss::gpu::StandardGpuResources();
}

gpuResource::gpuResource(const gpuResource&) {}

gpuResource& gpuResource::operator=(const gpuResource&){}

gpuResource::~gpuResource(){
    // if(res != NULL){
    //   delete res;
    // }
}

gpuResource* gpuResource::getInstance(){
  std::mutex lc;
  std::unique_lock<std::mutex> locker(lc);
  static gpuResource instance;
  locker.unlock();
  return &instance;
}
///****************************************************************************************