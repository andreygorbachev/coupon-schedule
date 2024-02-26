project(coupon-schedule-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  duration_variant.cpp
  date_adjuster.cpp
  quasi_coupon_schedule.cpp
  coupon_period.cpp
  coupon_schedule.cpp
  day_counts.cpp
  compounding_period.cpp
  compounding_schedule.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  coupon-schedule
#  Calendar::calendar
  calendar
  GTest::gtest_main
)

export(TARGETS coupon-schedule NAMESPACE CouponSchedule:: FILE CouponScheduleConfig.cmake)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
