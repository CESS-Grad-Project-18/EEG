#ifndef CAN_H
#define CAN_H


/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error frame */

/* valid bits in CAN ID for frame formats */
#define CAN_STD_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_XTD_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_CLR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

/*
 * Controller Area Network Identifier structure
 *
 * bit 0-28        : CAN identifier (11/29 bit)
 * bit 29        : error frame flag (0 = data frame, 1 = error frame)
 * bit 30        : remote transmission request flag (1 = rtr frame)
 * bit 31        : frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
typedef uint32 CanID_t;
typedef uint32 can_err_mask_t;


/*
 * Controller Area Network Error Frame Mask structure
 *
 * bit 0-28        : error class mask (see include/linux/can/error.h)
 * bit 29-31        : set to zero
 */

/**
 * struct can_frame - basic CAN frame structure
 * @can_id:  the CAN ID of the frame and CAN_*_FLAG flags, see above.
 * @can_dlc: the data length field of the CAN frame
 * @data:    the CAN frame payload.
 */
typedef struct {
        CanID_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
        __u8    can_dlc; /* data length code: 0 .. 8 */
        __u8    data[8] __attribute__((aligned(8)));
}Can_Frame;


/**
 * struct can_filter - CAN ID based filter in can_register().
 * @can_id:   relevant bits of CAN ID which are not masked out.
 * @can_mask: CAN mask (see description)
 *
 * Description:
 * A filter matches, when
 *
 *          <received_can_id> & mask == can_id & mask
 *
 * The filter can be inverted (CAN_INV_FILTER bit set in can_id) or it can
 * filter for error frames (CAN_ERR_FLAG bit set in mask).
 */
struct can_filter {
        CanID_t can_id;
        CanID_t can_mask;
};

#define CAN_INV_FILTER 0x20000000U /* to be set in can_filter.can_id */

#endif /* CAN_H */