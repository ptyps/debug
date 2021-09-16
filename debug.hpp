#pragma once

#include "pstd.hpp"

namespace debugging {
  namespace colors {
    static uint reset = 0;
    static uint bold = 1;
    static uint faint = 2;
    static uint underline = 4;
    static uint blink = 5;

    static uint black = 30;
    static uint red = 31;
    static uint green = 32;
    static uint yellow = 33;
    static uint blue = 34;
    static uint magenta = 35;
    static uint cyan = 36;
    static uint white = 37;
  }

  class Debug {    
    private:
      pstd::vstring name;
      bool enabled = !1;
      uint color;

    public:
      Debug(pstd::vstring name, uint color = colors::magenta) : name(name), color(color) {

      }

      void disable() {
        enabled = !1;
      }

      void enable() {
        enabled = !0;
      }

      template <typename ...A>
        void log(pstd::vstring str, A ...args) {
          if (!enabled)
            return;

          auto text = std::string();

          text += pstd::format("\x1b[%im", color);
          text += name;
          text += pstd::format("\x1b[%im", colors::reset);
          text += ": ";
          text += pstd::format(str, args ...);

          pstd::log(text); 
        }
  };
}
