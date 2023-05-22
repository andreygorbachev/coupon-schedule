add_library(coupon-schedule INTERFACE
  period.h
  quasi_coupon_schedule.h
  coupon_schedule.h
)

target_include_directories(coupon-schedule INTERFACE .)
