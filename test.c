#include <xdo.h>

int main() {
  const xdo_t *xdo = xdo_new(":0");
  xdo_send_keysequence_window((const xdo_t *)xdo, (Window)CURRENTWINDOW, "A", (useconds_t)0);
  return 0;
}
