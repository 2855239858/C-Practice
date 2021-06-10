#include "search_engine/feature_set.h"
#include "search_engine/search_engine.h"
#include "timer.hpp"
#include <iostream>
#include <kestrel.hh>
#include <memory>
#include <thread>
#include <vector>

using Kestrel::Keson;

std::shared_ptr<cstk::Index>
CreateIndexFromConfig(std::shared_ptr<cstk::Context> &ctxt,
                      const Keson::ValueRef &config);
cstk::SearchConfig
ParsingSearchConfigFromKeson(const Keson::ValueRef &cfg_keson);

///******************************************************************************************
// faiss::gpu::StandardGpuResources* cstk::gpuResource::res = NULL;
///******************************************************************************************

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <config>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  Timer::Timer timer;
  cstk::Logger::SetLogLevel(cstk::Logger::LL_TRACE);

  /************************json配置文件读取与解析*******************************/
  std::ifstream config_file(argv[1]);
  // std::ifstream config_file("../examples/config/pq_index.json");
  if (!config_file.is_open()) {
    fprintf(stderr, "failed to open the config file: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  std::istreambuf_iterator<char> is_iter(config_file);
  std::string config_contents(is_iter, std::istreambuf_iterator<char>());
  Keson::Value config_keson = Keson::Parse(config_contents);
  if (!config_keson.IsValid()) {
    kestrel_log(KESTREL_ERROR, "failed to parsing the config json\n");
    exit(EXIT_FAILURE);
  }
  config_file.close();
  /**************************读取测试数据*************************************/
  auto distractor_path =
      config_keson["test_data"]["distractor_db"].StringValue();
  auto distractor_num =
      config_keson["test_data"]["distractor_db_num"].IntValue();
  auto target_db_path = config_keson["test_data"]["target_db"].StringValue();
  auto target_db_num = config_keson["test_data"]["target_db_num"].IntValue();
  auto target_query_path =
      config_keson["test_data"]["target_query"].StringValue();
  auto target_query_num =
      config_keson["test_data"]["target_query_num"].IntValue();
  timer.StartTimer("LoadFeatures");
  auto distractors =
      cstk::LocalFeatureSet(distractor_path).GetFeatures(distractor_num);
  auto target_db =
      cstk::LocalFeatureSet(target_db_path).GetFeatures(target_db_num);
  auto target_query =
      cstk::LocalFeatureSet(target_query_path).GetFeatures(target_query_num);
  timer.StopTimer("LoadFeatures");
  timer.PrintTimer("LoadFeatures");
  for (size_t i = 0; i < distractors.size(); i++) {
    distractors[i].SetId(i);
  }
  for (size_t i = 0; i < target_db.size(); i++) {
    target_db[i].SetId(i + distractors.back().Id() + 1);
  }
  for (size_t i = 0; i < target_query.size(); i++) {
    target_query[i].SetId(i + target_db.back().Id() + 1);
  }

  cstk::SearchConfig search_config =
      ParsingSearchConfigFromKeson(config_keson["search_engine_search_config"]);

  /**************初始化SearchEngine的进程与线程环境**********************/
  timer.StartTimer("InitSearchEngine");
  cstk::SearchEngineInit("Kestrel", config_keson["license"].StringValue());
  timer.StopTimer("InitSearchEngine");
  timer.PrintTimer("InitSearchEngine");

  timer.StartTimer("CreateContext");
  const int32_t device_id = config_keson["device_id"].IntValue();
  const int32_t num_threads = config_keson["num_threads"].IntValue();
  const size_t reserved_memory_size =
      config_keson["reserved_memory_size"].IntValue();
  ////
  // std::vector<cstk::Context&> ctxt;
  // for(int i = 0; i < ctxt.size(); i++){
  //   auto tmp_ctxt = std::make_shared<cstk::Context>(device_id + i);
  //   tmp_ctxt->SetThreadNum(num_threads);
  //   ctxt.push_back(tmp_ctxt);
  // }
  auto ctxt1 = std::make_shared<cstk::Context>(device_id);
  ctxt1->SetThreadNum(num_threads);
  // auto ctxt2 = std::make_shared<cstk::Context>(device_id);
  // ctxt2->SetThreadNum(num_threads);
  // auto ctxt3 = std::make_shared<cstk::Context>(device_id);
  // ctxt3->SetThreadNum(num_threads);
  ///
  // auto ctxt = std::make_shared<cstk::Context>(device_id);
  // ctxt->SetThreadNum(num_threads);
  // ctxt->SetReservedMemorySize(reserved_memory_size);
  timer.StopTimer("CreateContext");
  timer.PrintTimer("CreateContext");

  /**********************创建SearchEngine实体************************/
  ////
  std::vector<std::shared_ptr<cstk::Index>> index(3);
  // for(int i = 0; i < 3; i++) index.push_back(new
  // std::shared_ptr<cstk::Index>);
  ////
  // std::shared_ptr<cstk::Index> index;
  if (config_keson.HasMember("input_serialized_file") &&
      !config_keson["input_serialized_file"].StringValue().empty()) {
    kestrel_log(KESTREL_TRACE, "create index from serialized file %s!\n",
                config_keson["input_serialized_file"].CStringValue());
    std::ifstream se_file(config_keson["input_serialized_file"].StringValue(),
                          std::ifstream::binary);
    if (!se_file.is_open()) {
      fprintf(stderr, "invalid serialized file path: %s\n",
              config_keson["input_serialized_file"].CStringValue());
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < index.size(); i++) {
      std::string name = "DeserializeSearchEngine " + std::to_string(i);
      timer.StartTimer(name);
      if (i == 0)
        index[i].reset(cstk::Index::CreateIndexFromStream(ctxt1, se_file));
      else if (i == 1)
        index[i].reset(cstk::Index::CreateIndexFromStream(ctxt1, se_file));
      else
        index[i].reset(cstk::Index::CreateIndexFromStream(ctxt1, se_file));
      timer.StopTimer(name);
      timer.PrintTimer(name);
    }
    // index.reset(cstk::Index::CreateIndexFromStream(ctxt, se_file));
    if (!config_keson["input_with_db"].BoolValue()) {
      for (int i = 0; i < index.size(); i++) {
        index[i]->Reset();
        std::string name = "AddFeatures " + std::to_string(i);
        timer.StartTimer(name);
        index[i]->AddFeatures(distractors);
        index[i]->AddFeatures(target_db);
        timer.StopTimer(name);
        timer.PrintTimer(name);
      }
    }
  } else {
    kestrel_log(KESTREL_TRACE, "create search engine from config!\n");
    std::vector<std::thread> threads;
    // for(int i = 0; i < index.size(); i++){
    // std::string name = "Create Index " + std::to_string(i);
    // threads.push_back(std::thread([&](){
    //   timer.StartTimer(name);
    //   if(i == 0) index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
    //   else if(i == 1) index[i] = CreateIndexFromConfig(ctxt1,
    //   config_keson.Ref());
    //   else index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
    //   timer.StopTimer(name);
    //   timer.PrintTimer(name);
    // /*****************训练************************/
    // name = "Train " + std::to_string(i);
    // timer.StartTimer(name);
    // int32_t num_sampling = config_keson["num_sampling_features"].IntValue();
    // auto sampling_features =
    // cstk::LocalFeatureSet(distractor_path).RandomSampling(num_sampling);
    // index[i]->Train(sampling_features);
    // timer.StopTimer(name);
    // timer.PrintTimer(name);

    // /***************** 添加特征 ******************/
    // name = "AddFeatures " + std::to_string(i);
    // timer.StartTimer(name);
    // index[i]->AddFeatures(distractors);
    // index[i]->AddFeatures(target_db);
    // timer.StopTimer(name);
    // timer.PrintTimer(name);
    // }));
    // }
    for (int i = 0; i < index.size(); i++) {
      std::string name = "Create Index " + std::to_string(i);
      timer.StartTimer(name);
      if (i == 0)
        index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
      else if (i == 1)
        index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
      else
        index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
      timer.StopTimer(name);
      timer.PrintTimer(name);
    }
    for (int i = 0; i < index.size(); i++) {
      std::string name = "Create Index " + std::to_string(i);
      // timer.StartTimer(name);
      // if(i == 0) index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
      // else if(i == 1) index[i] = CreateIndexFromConfig(ctxt1,
      // config_keson.Ref());
      // else index[i] = CreateIndexFromConfig(ctxt1, config_keson.Ref());
      // timer.StopTimer(name);
      // timer.PrintTimer(name);
      /*****************训练************************/
      name = "Train " + std::to_string(i);
      timer.StartTimer(name);
      int32_t num_sampling = config_keson["num_sampling_features"].IntValue();
      auto sampling_features =
          cstk::LocalFeatureSet(distractor_path).RandomSampling(num_sampling);
      index[i]->Train(sampling_features);
      timer.StopTimer(name);
      timer.PrintTimer(name);

      /***************** 添加特征 ******************/
      name = "AddFeatures " + std::to_string(i);
      timer.StartTimer(name);
      index[i]->AddFeatures(distractors);
      index[i]->AddFeatures(target_db);
      timer.StopTimer(name);
      timer.PrintTimer(name);
    }
  }

  // /***************** 搜索 **********************/
  // timer.StartTimer("Querying");
  // std::vector<std::vector<cstk::SearchResult>> results =
  //     index->Search(target_query, std::vector<cstk::IDFilter>{},
  //     search_config);
  // timer.StopTimer("Querying");
  // timer.PrintTimer("Querying");

  // /**************************序列化SearchEngine****************************/
  // if (config_keson.HasMember("output_serialized_file") &&
  //     !config_keson["output_serialized_file"].StringValue().empty()) {
  //   if (!config_keson["output_with_db"].BoolValue()) {
  //     index->Reset();
  //   }
  //   timer.StartTimer("Serialize Index");
  //   kestrel_log(KESTREL_TRACE, "serialize search engine to file: %s\n",
  //               config_keson["output_serialized_file"].CStringValue());
  //   std::ofstream
  //   serialized_file(config_keson["output_serialized_file"].StringValue(),
  //                                 std::ifstream::binary);
  //   if (!serialized_file.is_open()) {
  //     fprintf(stderr, "failed to open serialized file: %s\n",
  //             config_keson["output_serialized_file"].CStringValue());
  //     exit(EXIT_FAILURE);
  //   }
  //   index->SerializeToStream(serialized_file);
  //   timer.StopTimer("Serialize Index");
  //   timer.PrintTimer("Serialize Index");
  // }

  // /********************简单不严谨的统计一下准确率，并且将不正确的打印出来************************/
  // for (auto k : std::vector<int64_t>{1, 8, 16, 32, 64, 128, 256, 512, 1024})
  // {
  //   int32_t num_hits = 0;
  //   for (size_t i = 0; i < results.size(); i++) {
  //     bool hit = false;
  //     for (int32_t j = 0; j < std::min(k, search_config.k); j++) {
  //       if (results[i][j].index >= target_db.front().Id() &&
  //           results[i][j].index <= target_db.back().Id()) {
  //         hit = true;
  //       }
  //     }
  //     if (config_keson["print_error_query"].BoolValue() && !hit) {
  //       printf("query [%03zd]:", i);
  //       for (int32_t j = 0; j < std::min(k, 5L); j++) {
  //         printf(" %ld(%.4f)", results[i][j].index, results[i][j].score);
  //       }
  //       printf("\n");
  //     }
  //     num_hits += hit;
  //   }
  //   printf("(TopK=%04ld) There are %d (%.2f%%) queries hit the target db
  //   feature.\n", k, num_hits,
  //          100.0F * num_hits / target_query.size());
  // }

  for (int i = 0; i < index.size(); i++)
    index[i].reset();
  ctxt1.reset();
  // ctxt2.reset();
  // ctxt3.reset();
  cstk::SearchEngineDeinit();
  printf("TEST I AM HERE\n");

  exit(EXIT_SUCCESS);
}

std::shared_ptr<cstk::Index>
CreateIndexDC(std::shared_ptr<cstk::Context> &ctxt,
              const Keson::ValueRef &index_params) {
  int32_t feature_dim = index_params["feature_dim"].IntValue();
  int32_t nlist = index_params["nlist"].IntValue();
  int32_t nprobe = index_params["nprobe"].IntValue();
  std::string model = index_params["model"].StringValue();
  return std::shared_ptr<cstk::Index>(cstk::Index::CreateDeepCodeIndex(
      ctxt, model, feature_dim, nlist, nprobe));
}

std::shared_ptr<cstk::Index>
CreateIndexPQ(std::shared_ptr<cstk::Context> &ctxt,
              const Keson::ValueRef &index_params) {
  int32_t feature_dim = index_params["feature_dim"].IntValue();
  int32_t nlist = index_params["nlist"].IntValue();
  int32_t nprobe = index_params["nprobe"].IntValue();
  return std::shared_ptr<cstk::Index>(
      cstk::Index::CreatePQIndex(ctxt, feature_dim, nlist, nprobe));
}

std::shared_ptr<cstk::Index>
CreateIndexFlat(std::shared_ptr<cstk::Context> &ctxt,
                const Keson::ValueRef &index_params) {
  int32_t feature_dim = index_params["feature_dim"].IntValue();
  bool use_int8 = index_params["use_int8"].BoolValue();
  return std::shared_ptr<cstk::Index>(
      cstk::Index::CreateFlatIndex(ctxt, feature_dim, use_int8));
}

std::shared_ptr<cstk::Index>
CreateIndexHNSW(std::shared_ptr<cstk::Context> &ctxt,
                const Keson::ValueRef &index_params) {
  int32_t feature_dim = index_params["feature_dim"].IntValue();
  int32_t max_db_size = index_params["max_db_size"].IntValue();
  int32_t M = index_params["M"].IntValue();
  int32_t ef_construction = index_params["ef_construction"].IntValue();
  int32_t ef = index_params["ef"].IntValue();
  bool use_int8 = index_params["use_int8"].BoolValue();
  return std::shared_ptr<cstk::Index>(cstk::Index::CreateHNSWIndex(
      ctxt, feature_dim, max_db_size, M, ef_construction, ef, use_int8));
}

std::shared_ptr<cstk::Index>
CreateIndexExact(std::shared_ptr<cstk::Context> &ctxt,
                 const Keson::ValueRef &index_params) {
  int32_t feature_dim = index_params["feature_dim"].IntValue();
  bool use_int8 = index_params["use_int8"].BoolValue();
  auto rough_index = CreateIndexFromConfig(ctxt, index_params["rough_index"]);
  return std::shared_ptr<cstk::Index>(
      cstk::Index::CreateExactIndex(ctxt, rough_index, feature_dim, use_int8));
}

std::shared_ptr<cstk::Index>
CreateIndexFromConfig(std::shared_ptr<cstk::Context> &ctxt,
                      const Keson::ValueRef &config) {
  if (!config.HasMember("index_type")) {
    throw cstk::SearchEngineException("missing `index_type` key in the json.");
  }
  if (config["index_type"].StringValue() == "INDEX_DC") {
    return CreateIndexDC(ctxt, config["index_params"]);
  }
  if (config["index_type"].StringValue() == "INDEX_PQ") {
    return CreateIndexPQ(ctxt, config["index_params"]);
  }
  if (config["index_type"].StringValue() == "INDEX_FLAT") {
    return CreateIndexFlat(ctxt, config["index_params"]);
  }
  if (config["index_type"].StringValue() == "INDEX_HNSW") {
    return CreateIndexHNSW(ctxt, config["index_params"]);
  }
  if (config["index_type"].StringValue() == "INDEX_EXACT") {
    return CreateIndexExact(ctxt, config["index_params"]);
  }
  throw cstk::SearchEngineException("unrecognized index type value in json");
}

cstk::SearchConfig
ParsingSearchConfigFromKeson(const Keson::ValueRef &cfg_keson) {
  cstk::SearchConfig config;
  if (cfg_keson.HasMember("k")) {
    config.k = cfg_keson["k"].IntValue();
  }
  if (cfg_keson.HasMember("threshold")) {
    config.threshold = cfg_keson["threshold"].DoubleValue();
  }
  if (cfg_keson.HasMember("batch_size")) {
    config.batch_size = cfg_keson["batch_size"].IntValue();
  }

  kestrel_log(KESTREL_TRACE, "k = %zd\n", config.k);
  kestrel_log(KESTREL_TRACE, "threshold = %f\n", config.threshold);
  kestrel_log(KESTREL_TRACE, "batch_size = %zd\n", config.batch_size);

  if (cfg_keson.HasMember("dist_type")) {
    auto dist_type = cfg_keson["dist_type"].StringValue();
    kestrel_log(KESTREL_TRACE, "dist_type = %s\n", dist_type.c_str());
    if (dist_type == "inner_product") {
      config.dist_type = cstk::DistanceType::INNER_PRODUCT;
    } else if (dist_type == "L2") {
      config.dist_type = cstk::DistanceType::L2;
    } else {
      throw cstk::SearchEngineException("unknown distance type");
    }
  }
  cstk::IDFilter filter;
  if (cfg_keson.HasMember("id_filter")) {
    std::vector<int64_t> cids;
    filter.time_range[0] = cfg_keson["id_filter"]["time_begin"].IntValue();
    filter.time_range[1] = cfg_keson["id_filter"]["time_end"].IntValue();
    auto cid_value_vector = cfg_keson["id_filter"]["camera"].ToVector();
    for (auto &value_ref : cid_value_vector) {
      auto camera_id = value_ref.IntValue();
      filter.camera_id_mask[camera_id / 8] |= (0x01 << (camera_id % 8));
    }
    kestrel_log(KESTREL_TRACE, "filter time start = %d\n",
                filter.time_range[0]);
    kestrel_log(KESTREL_TRACE, "filter time end = %d\n", filter.time_range[1]);
    kestrel_log(KESTREL_TRACE, "filter camera list size = %zu\n",
                cid_value_vector.size());
  }
  return config;
}
