add_library(coupon-schedule INTERFACE
  quasi_coupon_schedule.h
  period.h
)

target_include_directories(coupon-schedule INTERFACE .)
