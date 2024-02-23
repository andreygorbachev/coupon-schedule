project("coupon-schedule")

add_library(${PROJECT_NAME} INTERFACE
  duration_variant.h
  coupon_period.h
  quasi_coupon_schedule.h
  coupon_schedule.h
  day_count_interface.h
  day_counts.h
  compounding_period.h
  compounding_schedule.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)
