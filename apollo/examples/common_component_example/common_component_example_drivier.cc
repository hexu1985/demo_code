/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "cyber/cyber.h"
#include "cyber/examples/proto/examples.pb.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"
#include <thread>
#include <chrono>

using apollo::cyber::Rate;
using apollo::cyber::Time;
using apollo::cyber::examples::proto::Driver;

int main(int argc, char *argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);

  // create talker node
  auto talker_node = apollo::cyber::CreateNode("common_component_example_drivier");

  auto thread_1 = std::thread([&talker_node]() {
          auto talker = talker_node->CreateWriter<Driver>("/apollo/test");
          Rate rate(1.0);
          while (apollo::cyber::OK()) {
            static uint64_t seq = 0;
            auto msg = std::make_shared<Driver>();
            msg->set_content("Hello, apollo from /apollo/test!");
            msg->set_msg_id(seq++);
            msg->set_timestamp(Time::Now().ToNanosecond());
            talker->Write(msg);
            AINFO << "talker sent a test message!";
            rate.Sleep();
          }
          }); 

  // create talker
  auto talker = talker_node->CreateWriter<Driver>("/apollo/prediction");
  Rate rate(1.0);
  while (apollo::cyber::OK()) {
    static uint64_t seq = 10000;
    auto msg = std::make_shared<Driver>();
    msg->set_content("Hello, apollo from /apollo/prediction!");
    msg->set_msg_id(seq++);
    msg->set_timestamp(Time::Now().ToNanosecond());
    talker->Write(msg);
    AINFO << "talker sent a prediction message!";
    rate.Sleep();
  }

  thread_1.join();

  return 0;
}
