#pragma once

#include <string>

namespace debugging {
  namespace colors {
    static uint RESET = 0;
    static uint BOLD = 1;
    static uint FAINT = 2;
    static uint UNDERLINE = 4;
    static uint BLINK = 5;

    static uint BLACK = 30;
    static uint RED = 31;
    static uint GREEN = 32;
    static uint YELLOW = 33;
    static uint BLUE = 34;
    static uint MAGENTA = 35;
    static uint CYAN = 36;
    static uint WHITE = 37;
  }

  using vstring = std::string_view;

  class Debug {    
    private:
      bool enabled = !1;
      vstring name;
      uint color;

    public:
      Debug(vstring name, uint color = colors::MAGENTA) : name(name), color(color) {

      }

      void disable() {
        enabled = !1;
      }

      void enable() {
        enabled = !0;
      }

      template <typename ...A>
        void log(vstring str, A ...args) {
          if (!enabled)
            return;

          auto text = std::string();

          text += "\x1b[";
          text += std::to_string(color);
          text += "m";
          text += name;
          text += "\x1b[0m: ";

          auto length = std::snprintf(nullptr, 0, &str[0], args...);
          auto out = std::string(length, '\0');
          std::sprintf(&out[0], &str[0], args...);
          text += out.data();

          printf(&text[0]);
          printf("\n");
        }
  };
}
