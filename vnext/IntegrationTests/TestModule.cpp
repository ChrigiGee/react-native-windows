// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "TestModule.h"

using namespace facebook::xplat;
using namespace folly;

using std::function;
using std::map;
using std::move;
using std::string;
using std::vector;

namespace Microsoft::React::Test {

#pragma region TestModule members

/*static*/ string TestModule::name = "TestModule";

TestModule::TestModule(function<void(bool)> &&testPassedHandler) : m_testPassedHandler{move(testPassedHandler)} {}

#pragma region TestModule.js methods

void TestModule::sendAppEvent(const string &name) {}

void TestModule::markTestPassed(bool success) {
  m_testPassedHandler(success);
}

void TestModule::markTestCompleted() {
  markTestPassed(true);
}

void TestModule::shouldResolve() {}

#pragma endregion TestModule.js methods

string TestModule::getName() {
  return name;
}

map<string, dynamic> TestModule::getConstants() {
  return {};
}

vector<module::CxxModule::Method> TestModule::getMethods() {
  return {
      Method(
          "sendAppEvent",
          [this](dynamic args) {
            this->sendAppEvent(jsArgAsString(args, 0)); // TODO: 2nd arg?
          }),
      Method("markTestCompleted", [this](dynamic args) { this->markTestCompleted(); }),
      Method("markTestPassed", [this](dynamic args) { this->markTestPassed(jsArgAsBool(args, 0)); }),
      Method("shouldResolve", [this](dynamic args) { shouldResolve(); }),
  };
}

#pragma endregion TestModule members

#pragma region TestDeviceInfoModule members

/*static*/ string TestDeviceInfoModule::name = "DeviceInfo";

TestDeviceInfoModule::TestDeviceInfoModule() {}

string TestDeviceInfoModule::getName() {
  return name;
}

auto TestDeviceInfoModule::getConstants() -> map<string, dynamic> {
  return {{"Dimensions",
           folly::dynamic::object(
               "windowPhysicalPixels",
               folly::dynamic::object("width", 100)("height", 100)("scale", 1)("fontScale", 1)("densityDpi", 1))(
               "screenPhysicalPixels",
               folly::dynamic::object("width", 100)("height", 100)("scale", 1)("fontScale", 1)("densityDpi", 1))}};
}

auto TestDeviceInfoModule::getMethods() -> vector<Method> {
  return {};
}

#pragma endregion TestDeviceInfoModule members

#pragma region TestAppStateModule members

/*static*/ string TestAppStateModule::name = "AppState";

TestAppStateModule::TestAppStateModule() {}

string TestAppStateModule::getName() {
  return name;
}

auto TestAppStateModule::getConstants() -> map<string, dynamic> {
  return {{"initialAppState", "active"}};
}

auto TestAppStateModule::getMethods() -> vector<Method> {
  return {Method(
      "getCurrentAppState",
      [this](folly::dynamic args, Callback cbSuccess, Callback /*cbFailure*/) {
        cbSuccess({folly::dynamic::object("app_state", "active")});
      },
      AsyncTag)};
}

#pragma endregion TestAppStateModule members

} // namespace Microsoft::React::Test
