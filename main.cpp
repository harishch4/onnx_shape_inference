#include <fstream>
#include <iostream>
#include <vector>
#include "onnx/defs/schema.h"
#include "onnx/defs/shape_inference.h"
#include "onnx/onnx_pb.h"
#include "onnx/defs/parser.h"
#include "onnx/shape_inference/implementation.h"

int main(int, char **) {
  std::ifstream input("/home/harry/onnx-parser/model.onnx",
                      std::ios::ate |
                          std::ios::binary); // open file and move current
                                             // position in file to the end

  std::streamsize size = input.tellg(); // get current position in file
  input.seekg(0, std::ios::beg);        // move to start of file
  std::vector<char> buffer(size);
  input.read(buffer.data(), size); // read raw data

  onnx::ModelProto model;
  model.ParseFromArray(buffer.data(), size); // parse protobuf

  ONNX_NAMESPACE::shape_inference::InferShapes(model);
  auto graph = model.graph();

  for (size_t i = 0; i < graph.value_info_size(); i++) {
    const onnx::ValueInfoProto info = graph.value_info(i);
    std::string name = info.name();
    auto shape = info.type().tensor_type().shape();
    if (shape.dim_size() > 0) {
      int size = shape.dim_size();
      std::cout << name << " :" << shape.dim(0).dim_param();
      for (int i = 1; i < size; ++i)
      {
        std::cout << shape.dim(i).dim_value() << ", ";
      }
      std::cout << std::endl;
    }
  }
}
