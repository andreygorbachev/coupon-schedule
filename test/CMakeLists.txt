project(coupon-schedule-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  period.cpp
  quasi_coupon_schedule.cpp
  coupon_schedule.cpp
  day_count_fractions.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  coupon-schedule
  Calendar::calendar
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
