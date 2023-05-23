add_library(coupon-schedule INTERFACE
  period.h
  quasi_coupon_schedule.h
  coupon_schedule.h
  day_count_interface.h
  day_counts.h
)

target_include_directories(coupon-schedule INTERFACE .)
