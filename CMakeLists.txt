cmake_minimum_required(VERSION 3.15)

project("coupon-schedule" VERSION 0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

find_package(Calendar)

enable_testing()

add_subdirectory(include)
add_subdirectory(test)

export(TARGETS coupon-schedule NAMESPACE CouponSchedule:: FILE CouponScheduleConfig.cmake)

set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE CouponSchedule)
