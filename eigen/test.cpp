#include <eigen3/Eigen/Core>
#include <iostream>
#include <memory>
#include <unsupported/Eigen/CXX11/Tensor>
typedef Eigen::Tensor<float, 1, Eigen::RowMajor> Tensor1f;
typedef Eigen::Tensor<float, 2, Eigen::RowMajor> Tensor2f;
typedef Eigen::Tensor<float, 3, Eigen::RowMajor> Tensor3f;
typedef Eigen::Tensor<float, 4, Eigen::RowMajor> Tensor4f;

typedef Eigen::TensorMap<Tensor1f> Tensor1fRef;
typedef Eigen::TensorMap<Tensor2f> Tensor2fRef;
typedef Eigen::TensorMap<Tensor3f> Tensor3fRef;
typedef Eigen::TensorMap<Tensor4f> Tensor4fRef;

typedef std::shared_ptr<Tensor1fRef> spTensor1fRef;
typedef std::shared_ptr<Tensor2fRef> spTensor2fRef;
typedef std::shared_ptr<Tensor3fRef> spTensor3fRef;
typedef std::shared_ptr<Tensor4fRef> spTensor4fRef;

typedef Eigen::Tensor<int, 0, Eigen::RowMajor> Tensor0i;
typedef Eigen::Tensor<int, 1, Eigen::RowMajor> Tensor1i;
typedef Eigen::Tensor<int, 2, Eigen::RowMajor> Tensor2i;
typedef Eigen::Tensor<int, 3, Eigen::RowMajor> Tensor3i;
typedef Eigen::Tensor<int, 4, Eigen::RowMajor> Tensor4i;

typedef Eigen::Tensor<bool, 1, Eigen::RowMajor> Tensor1b;
typedef Eigen::Tensor<bool, 2, Eigen::RowMajor> Tensor2b;
typedef Eigen::Tensor<bool, 3, Eigen::RowMajor> Tensor3b;
typedef Eigen::Tensor<bool, 4, Eigen::RowMajor> Tensor4b;

typedef Eigen::array<long, 1> Array1l;

typedef Eigen::array<long, 2> Array21;
typedef Eigen::array<long, 3> Array3l;
typedef Eigen::array<long, 4> Array4l;

typedef Eigen::Tensor<Eigen::DenseIndex, 1, Eigen::RowMajor> Idx1f;
typedef Eigen::Tensor<Eigen::DenseIndex, 2, Eigen::RowMajor> Idx2f;

template <typename T>
using MatrixType = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Scalar, int rank, typename sizeType>
auto Tensor_to_Matrix(const Eigen::Tensor<Scalar, rank> &tensor,
                      const sizeType rows, const sizeType cols) {
  return Eigen::Map<const MatrixType<Scalar>>(tensor.data(), rows, cols);
}

template <typename Tensor> static std::vector<float> run(const Tensor &tensor) {
  typedef typename Eigen::internal::remove_const<typename Tensor::Scalar>::type
      Scalar;
  typedef typename Tensor::Index Index;
  const Index total_size = Eigen::internal::array_prod(tensor.dimensions());
  std::vector<float> result;

  if (total_size > 0) {
    Eigen::Map<const Eigen::Array<Scalar, Eigen::Dynamic, 1>> array(
        const_cast<Scalar *>(tensor.data()), total_size);
    std::cout << array[0] << std::endl;
    for (auto i = 0u; i < total_size; ++i) {
      result.push_back(array[i]);
    }

    // os << array;
  }
  return result;
};

int main() {
  Eigen::Matrix<double, 4, 4> mat;
  mat.setRandom();
  Idx1f test;
  Array21 a2;

  Tensor3f t3(1, 2, 3);
  Eigen::Tensor<float, 2> y(2, 3);
  y.setRandom();
  std::cout << y << std::endl;
  std::cout << t3 << std::endl;

  std::cout << Tensor_to_Matrix(y, 2, 3) << std::endl;
  run(t3);

  // auto vm = VectorMap(t3);
  // std::cout << vm << std::endl;

  // std::cout << "y = " << y.format(Eigen::TensorIOFormat::Native()) <<
  // std::endl;
  return 0;
}
