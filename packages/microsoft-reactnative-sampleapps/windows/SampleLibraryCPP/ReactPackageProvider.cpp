// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "CircleViewManagerCpp.h"
#include "CustomUserControlViewManagerCpp.h"
#include "SampleModuleCpp.h"

// Generated spec files
#include "..\..\codegen\NativeMyModuleSpec.g.h"

#include "MyModule.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::SampleLibraryCpp::implementation {

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept {
  AddAttributedModules(packageBuilder);

  packageBuilder.AddModule(
      L"MyModule", MakeTurboModuleProvider<::SampleLibraryCpp::MyModule, ::SampleLibraryCpp::MyModuleSpec>());
  packageBuilder.AddViewManager(
      L"CustomUserControlViewManagerCpp", []() { return winrt::make<CustomUserControlViewManagerCpp>(); });
  packageBuilder.AddViewManager(L"CircleViewManagerCpp", []() { return winrt::make<CircleViewManagerCpp>(); });
}

} // namespace winrt::SampleLibraryCpp::implementation
