/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hdfspp/status.h"

#include <cassert>
#include <sstream>

namespace hdfs {

Status::Status(int code, const char *msg1) : code_(code) {
  if(msg1) {
    msg_ = msg1;
  }
}

Status::Status(int code, const char *msg1, const char *msg2) : code_(code) {
  std::stringstream ss;
  if(msg1) {
    ss << msg1;
    if(msg2) {
      ss << ":" << msg2;
    }
  }
  msg_ = ss.str();
}


Status Status::OK() {
  return Status();
}

Status Status::InvalidArgument(const char *msg) {
  return Status(kInvalidArgument, msg);
}

Status Status::ResourceUnavailable(const char *msg) {
  return Status(kResourceUnavailable, msg);
}

Status Status::Unimplemented() {
  return Status(kUnimplemented, "");
}

Status Status::Exception(const char *exception_class_name, const char *error_message) {
  return Status(kException, exception_class_name, error_message);
}

Status Status::Error(const char *error_message) {
  return Exception("Exception", error_message);
}

Status Status::Canceled() {
  return Status(kOperationCanceled,"Operation canceled");
}


std::string Status::ToString() const {
  if (code_ == kOk) {
    return "OK";
  }
  return msg_;
}

}