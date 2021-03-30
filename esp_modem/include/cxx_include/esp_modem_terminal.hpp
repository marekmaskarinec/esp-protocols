// Copyright 2021 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _ESP_MODEM_TERMINAL_HPP_
#define _ESP_MODEM_TERMINAL_HPP_

#include <memory>
#include <functional>
#include <exception>
#include <cstddef>
#include <cstdint>
#include <utility>
#include "esp_err.h"
#include "esp_modem_primitives.hpp"

namespace esp_modem {

enum class terminal_error {
    BUFFER_OVERFLOW,
    CHECKSUM_ERROR,
    UNEXPECTED_CONTROL_FLOW,
};

class Terminal {
public:
    virtual ~Terminal() = default;

    virtual void set_data_cb(std::function<bool(size_t len)> f) { on_data = std::move(f); }

    void set_error_cb(std::function<void(terminal_error)> f) { on_error = std::move(f); }

    virtual int write(uint8_t *data, size_t len) = 0;

    virtual int read(uint8_t *data, size_t len) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual size_t max_virtual_terms() { return 1; }

protected:
    std::function<bool(size_t len)> on_data;
    std::function<void(terminal_error)> on_error;
};

} // namespace esp_modem

#endif // _ESP_MODEM_TERMINAL_HPP_