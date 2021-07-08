/*
 * parser_interface.hpp
 *
 * Created on: Jul 08, 2021 14:43
 * Description:
 *
 * Copyright (c) 2021 Weston Robot Pte. Ltd.
 */

#ifndef PASER_INTERFACE_HPP
#define PASER_INTERFACE_HPP

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __linux__
#include <linux/can.h>
#else
struct can_frame {
  uint32_t can_id;
  uint8_t can_dlc;
  uint8_t data[8] __attribute__((aligned(8)));
};
#endif

#include "ugv_sdk/interface/agilex_message.h"

struct ParserInterface {
  // CAN support
  virtual bool DecodeMessage(const struct can_frame *rx_frame,
                             AgxMessage *msg) = 0;
  virtual void EncodeMessage(const AgxMessage *msg,
                              struct can_frame *tx_frame) = 0;
  virtual uint8_t CalculateChecksum(uint16_t id, uint8_t *data,
                                    uint8_t dlc) = 0;

  // UART support
  virtual bool DecodeMessage(uint8_t *data, uint8_t dlc, AgxMessage *msg){
      // throw exception
  };
  virtual void EncodeMessage(const AgxMessage *msg, uint8_t *buf, uint8_t *len){
      // throw exception
  };
  virtual uint8_t CalculateChecksum(uint8_t *buf, uint8_t len){
      // throw exception
  };
};

#endif /* PASER_INTERFACE_HPP */