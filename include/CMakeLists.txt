project("coupon-schedule")

add_library(${PROJECT_NAME} INTERFACE
  duration_variant.h
  date_adjuster_interface.h
  date_adjusters.h
  quasi_coupon_schedule.h
  coupon_period.h
  coupon_schedule.h
  day_count_interface.h
  day_counts.h
  compounding_period.h
  compounding_schedule.h
)

target_include_directories(${PROJECT_NAME} INTERFACE .)
