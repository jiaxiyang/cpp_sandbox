#include <filesystem>
#include <fstream>
#include <glog/logging.h>
#include <iostream>
#include <libyuv.h>
#include <vector>

#include <chrono>

using Clock = std::chrono::steady_clock;

#define __TIC__(tag) auto __##tag##_start_time = Clock::now();

#define __TOC__(tag)                                                           \
  auto __##tag##_end_time = Clock::now();                                      \
  std::cout << #tag << " : "                                                   \
            << std::chrono::duration_cast<std::chrono::microseconds>(          \
                   __##tag##_end_time - __##tag##_start_time)                  \
                   .count()                                                    \
            << "us" << std::endl;

template <typename T> std::vector<T> read_bin_file(std::string file) {
  auto file_size = std::filesystem::file_size(file);
  CHECK(file_size % sizeof(T) == 0);
  auto result_size = file_size / sizeof(T);
  std::vector<T> result(result_size);
  CHECK(std::ifstream(file).read((char *)&result[0], file_size).good())
      << "Failed to read baseline from " << file;
  return result;
}

template <typename T> void write_file(T *src, int size, std::string filename) {
  std::ofstream ofs;
  ofs.open(filename, ofs.binary);
  if (!ofs) {
    std::cout << "Can't open the file! " << filename << "\n";
    return;
  }
  ofs.write((char *)src, size * sizeof(T));
  ofs.close();
}

void I420ToNv12(uint8_t *src_i420_data, int width, int height,
                uint8_t *src_nv12_data) {
  int src_y_size = width * height;
  int src_u_size = (width >> 1) * (height >> 1);

  uint8_t *src_nv12_y_data = src_nv12_data;
  uint8_t *src_nv12_uv_data = src_nv12_data + src_y_size;

  uint8_t *src_i420_y_data = src_i420_data;
  uint8_t *src_i420_u_data = src_i420_data + src_y_size;
  uint8_t *src_i420_v_data = src_i420_data + src_y_size + src_u_size;

  libyuv::I420ToNV12(src_i420_y_data, width, src_i420_u_data, width >> 1,
                     src_i420_v_data, width >> 1, src_nv12_y_data, width,
                     src_nv12_uv_data, width, width, height);
}

// ConvertToI420 and use for to convert to  NV12
int crop1() {
  auto nv12 = read_bin_file<uint8_t>("nv12_1080p.yuv");
  LOG(INFO) << "nv12.size()=" << nv12.size();
  int src_width = 1920;
  int src_height = 1080;

  __TIC__(CROP1)

  std::vector<uint8_t> result(nv12.size() / 4);
  std::vector<uint8_t> u(result.size() / 3 / 2);
  std::vector<uint8_t> v(result.size() / 3 / 2);
  LOG(INFO) << "result.size()=" << result.size();
  int crop_width = src_width / 2;
  int crop_height = src_height / 2;
  size_t y_size = crop_width * crop_height;
  size_t u_size = crop_width * crop_height / 4;
  size_t v_size = crop_width * crop_height / 4;
  LOG(INFO) << "y_size=" << y_size << " " //
            << "u_size=" << u_size << " " //
            << "v_size=" << v_size;
  int y_stride = crop_width;
  // int u_stride = crop_width / 4;
  // NOTE: u_stride: (crop_width + 1) / 2
  int u_stride = (crop_width + 1) / 2;
  int v_stride = (crop_width + 1) / 2;
  // int v_stride = crop_width / 4;
  LOG(INFO) << "y_stride=" << y_stride << " " //
            << "u_stride=" << u_stride << " " //
            << "v_stride=" << v_stride;
  // test center crop
  __TIC__(CROP)
  auto ret = libyuv::ConvertToI420(
      &nv12[0], nv12.size(), &result[0], y_stride, &u[0], u_stride, &v[0],
      v_stride, src_width / 4, src_height / 4, src_width, src_height,
      crop_width, crop_height, libyuv::kRotate0, libyuv::FOURCC_NV12);
  __TOC__(CROP)

  LOG(INFO) << "ret=" << ret;

  __TIC__(I420ToNV12)
  for (auto i = 0u; i < u_size; ++i) {
    result[y_size + 2 * i] = u[i];
    result[y_size + 2 * i + 1] = v[i];
  }
  __TOC__(I420ToNV12)
  __TOC__(CROP1)

  write_file(&result[0], result.size(), "libyuv_nv12_center_crop1.yuv");
  return 0;
}

// ConvertToI420 and use I420ToNV12 to convert to NV12
int crop2() {
  auto nv12 = read_bin_file<uint8_t>("nv12_1080p.yuv");
  LOG(INFO) << "nv12.size()=" << nv12.size();
  int src_width = 1920;
  int src_height = 1080;

  __TIC__(CROP2)
  std::vector<uint8_t> result(nv12.size() / 4);
  LOG(INFO) << "result.size()=" << result.size();
  int crop_width = src_width / 2;
  int crop_height = src_height / 2;
  size_t y_size = crop_width * crop_height;
  size_t u_size = crop_width * crop_height / 4;
  size_t v_size = crop_width * crop_height / 4;
  LOG(INFO) << "y_size=" << y_size << " " //
            << "u_size=" << u_size << " " //
            << "v_size=" << v_size;
  int y_stride = crop_width;
  // int u_stride = crop_width / 4;
  // NOTE: u_stride: (crop_width + 1) / 2
  int u_stride = (crop_width + 1) / 2;
  int v_stride = (crop_width + 1) / 2;
  // int v_stride = crop_width / 4;
  LOG(INFO) << "y_stride=" << y_stride << " " //
            << "u_stride=" << u_stride << " " //
            << "v_stride=" << v_stride;
  // test center crop
  __TIC__(CROP)
  auto ret = libyuv::ConvertToI420(
      &nv12[0], nv12.size(), &result[0], y_stride, &result[y_size], u_stride,
      &result[y_size + u_size], v_stride, src_width / 4, src_height / 4,
      src_width, src_height, crop_width, crop_height, libyuv::kRotate0,
      libyuv::FOURCC_NV12);
  __TOC__(CROP)

  LOG(INFO) << "ret=" << ret;

  std::vector<uint8_t> result1(result.size());
  __TIC__(I420ToNv12)
  I420ToNv12(&result[0], crop_width, crop_height, &result1[0]);
  __TOC__(I420ToNv12)
  __TOC__(CROP2)

  write_file(&result1[0], result1.size(), "libyuv_nv12_center_crop2.yuv");

  return 0;
}

int main(int argc, char *argv[]) {
  crop1();
  crop2();

  return 0;
}

// int ConvertToI420(const uint8_t* sample,
//                   size_t sample_size,
//                   uint8_t* dst_y,
//                   int dst_stride_y,
//                   uint8_t* dst_u,
//                   int dst_stride_u,
//                   uint8_t* dst_v,
//                   int dst_stride_v,
//                   int crop_x,
//                   int crop_y,
//                   int src_width,
//                   int src_height,
//                   int crop_width,
//                   int crop_height,
//                   enum RotationMode rotation,
//                   uint32_t fourcc);

// int I420ToNV12(const uint8_t* src_y,
//                int src_stride_y,
//                const uint8_t* src_u,
//                int src_stride_u,
//                const uint8_t* src_v,
//                int src_stride_v,
//                uint8_t* dst_y,
//                int dst_stride_y,
//                uint8_t* dst_uv,
//                int dst_stride_uv,
//                int width,
//                int height)
