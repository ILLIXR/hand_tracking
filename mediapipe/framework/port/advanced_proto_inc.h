// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// advanced_proto_inc.h includes all the proto header files used by mediapipe
// framework code, and it should only be used by a limited number of files that
// do advanced proto template parsing and I/O.
#ifndef MEDIAPIPE_PORT_ADVANCED_PROTO_INC_H_
#define MEDIAPIPE_PORT_ADVANCED_PROTO_INC_H_

#include "google/protobuf/descriptor.h"
#include "google/protobuf/descriptor.pb.h"
#include "google/protobuf/descriptor_database.h"
#include "google/protobuf/dynamic_message.h"
#include "google/protobuf/io/gzip_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/message.h"
#include "mediapipe/framework/port.h"
#include "mediapipe/framework/port/advanced_proto_lite_inc.h"
#include "mediapipe/framework/port/core_proto_inc.h"
#include "mediapipe/framework/port/proto_ns.h"

#endif // MEDIAPIPE_PORT_ADVANCED_PROTO_INC_H_
