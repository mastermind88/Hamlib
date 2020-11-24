/*
 *  Hamlib Interface - Rotator API header
 *  Copyright (c) 2000-2005 by Stephane Fillod
 *
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef _ROTATOR_H
#define _ROTATOR_H 1

#include <hamlib/rig.h>
#include <hamlib/rotlist.h>

/**
 * \addtogroup rotator
 * @{
 */

/**
 *  \file rotator.h
 *  \brief Hamlib rotator data structures.
 *
 *  This file contains the data structures and declarations for the Hamlib
 *  rotator API.  see the rotator.c file for more details on the rotator API.
 */



__BEGIN_DECLS

/* Forward struct references */

struct rot;
struct rot_state;


/**
 *  \typedef typedef struct s_rot ROT
 *  \brief Rotator structure definition (see rot for details).
 */
typedef struct s_rot ROT;


/**
 *  \typedef typedef float elevation_t
 *  \brief Type definition for elevation.
 *
 *  The elevation_t type is used as parameter for the rot_set_position() and
 *  rot_get_position() functions.
 *
 *  Unless specified otherwise, the unit of elevation_t is decimal degrees.
 */
typedef float elevation_t;


/**
 *  \typedef typedef float azimuth_t
 *  \brief Type definition for azimuth.
 *
 *  The azimuth_t type is used as parameter for the rot_set_position() and
 *  rot_get_position() functions.
 *
 *  Unless specified otherwise, the unit of azimuth_t is decimal degrees.
 */
typedef float azimuth_t;


/**
 * \brief Token in the netrotctl protocol for returning error code
 */
#define NETROTCTL_RET "RPRT "


/**
 *  \def ROT_RESET_ALL
 *  \brief A macro that returns the flag for the \b reset operation.
 *  \sa rot_reset(), rot_reset_t()
 */
#define ROT_RESET_ALL   1


/**
 *  \typedef typedef int rot_reset_t
 *  \brief Type definition for rotator reset.
 *
 *  The rot_reset_t type is used as parameter for the rot_reset() API
 *  function.
 */
typedef int rot_reset_t;


//! @cond Doxygen_Suppress
/**
 * \brief Rotator type flags
 */
typedef enum {
    ROT_FLAG_AZIMUTH =      (1 << 1),   /*!< Azimuth */
    ROT_FLAG_ELEVATION =    (1 << 2)    /*!< Elevation */
} rot_type_t;

#define ROT_TYPE_MASK (ROT_FLAG_AZIMUTH|ROT_FLAG_ELEVATION)

#define ROT_TYPE_OTHER      0
#define ROT_TYPE_AZIMUTH    ROT_FLAG_AZIMUTH
#define ROT_TYPE_ELEVATION  ROT_FLAG_ELEVATION
#define ROT_TYPE_AZEL       (ROT_FLAG_AZIMUTH|ROT_FLAG_ELEVATION)
//! @endcond


/**
 *  \def ROT_MOVE_UP
 *  \brief A macro that returns the flag for the \b UP direction.
 *
 *  This macro defines the value of the \b UP direction which can be
 *  used with the rot_move() function.
 *
 *  \sa rot_move(), ROT_MOVE_DOWN, ROT_MOVE_LEFT, ROT_MOVE_CCW,
 *      ROT_MOVE_RIGHT, ROT_MOVE_CW
 */
#define ROT_MOVE_UP         (1<<1)

/**
 *  \def ROT_MOVE_DOWN
 *  \brief A macro that returns the flag for the \b DOWN direction.
 *
 *  This macro defines the value of the \b DOWN direction which can be
 *  used with the rot_move() function.
 *
 *  \sa rot_move(), ROT_MOVE_UP, ROT_MOVE_LEFT, ROT_MOVE_CCW, ROT_MOVE_RIGHT,
 *      ROT_MOVE_CW
*/
#define ROT_MOVE_DOWN       (1<<2)

/**
 *  \def ROT_MOVE_LEFT
 *  \brief A macro that returns the flag for the \b LEFT direction.
 *
 *  This macro defines the value of the \b LEFT direction which can be
 *  used with the rot_move function.
 *
 *  \sa rot_move(), ROT_MOVE_UP, ROT_MOVE_DOWN, ROT_MOVE_CCW, ROT_MOVE_RIGHT,
 *      ROT_MOVE_CW
 */
#define ROT_MOVE_LEFT       (1<<3)

/**
 *  \def ROT_MOVE_CCW
 *  \brief A macro that returns the flag for the \b counterclockwise direction.
 *
 *  This macro defines the value of the \b counterclockwise direction which
 *  can be used with the rot_move() function. This value is equivalent to
 *  ROT_MOVE_LEFT .
 *
 *  \sa rot_move(), ROT_MOVE_UP, ROT_MOVE_DOWN, ROT_MOVE_LEFT, ROT_MOVE_RIGHT,
 *      ROT_MOVE_CW
 */
#define ROT_MOVE_CCW        ROT_MOVE_LEFT

/**
 *  \def ROT_MOVE_RIGHT
 *  \brief A macro that returns the flag for the \b RIGHT direction.
 *
 *  This macro defines the value of the \b RIGHT direction which can be used
 *  with the rot_move() function.
 *
 *  \sa rot_move(), ROT_MOVE_UP, ROT_MOVE_DOWN, ROT_MOVE_LEFT, ROT_MOVE_CCW,
 *      ROT_MOVE_CW
 */
#define ROT_MOVE_RIGHT      (1<<4)

/**
 *  \def ROT_MOVE_CW
 *  \brief A macro that returns the flag for the \b clockwise direction.
 *
 *  This macro defines the value of the \b clockwise direction which can be
 *  used with the rot_move() function. This value is equivalent to
 *  ROT_MOVE_RIGHT .
 *
 *  \sa rot_move(), ROT_MOVE_UP, ROT_MOVE_DOWN, ROT_MOVE_LEFT, ROT_MOVE_CCW,
 *      ROT_MOVE_RIGHT
 */
#define ROT_MOVE_CW         ROT_MOVE_RIGHT


/**
 * \brief Rotator status flags
 */
typedef enum {
    ROT_STATUS_BUSY =              (1 << 1), /*!< Rotator is busy, not accepting commands */
    ROT_STATUS_MOVING =            (1 << 2), /*!< Rotator is currently moving (direction type not specified) */
    ROT_STATUS_MOVING_AZ =         (1 << 3), /*!< Azimuth rotator is currently moving */
    ROT_STATUS_MOVING_EL =         (1 << 4), /*!< Elevation rotator is currently moving */
    ROT_STATUS_UP_LIMIT =          (1 << 5), /*!< The elevation rotator has reached its limit to move up */
    ROT_STATUS_DOWN_LIMIT =        (1 << 6), /*!< The elevation rotator has reached its limit to move down */
    ROT_STATUS_LEFT_LIMIT =        (1 << 7), /*!< The azimuth rotator has reached its limit to move left (CCW) */
    ROT_STATUS_RIGHT_LIMIT =       (1 << 8), /*!< The azimuth rotator has reached its limit to move right (CW) */
    ROT_STATUS_UP_OVERLAP =        (1 << 9), /*!< The elevation rotator has rotated up past 360 degrees */
    ROT_STATUS_DOWN_OVERLAP =      (1 << 10), /*!< The elevation rotator has rotated down past 0 degrees */
    ROT_STATUS_LEFT_OVERLAP =      (1 << 11), /*!< The azimuth rotator has rotated left (CCW) past 0 degrees */
    ROT_STATUS_RIGHT_OVERLAP =     (1 << 12), /*!< The azimuth rotator has rotated right (CW) past 360 degrees */
} rot_status_t;


/**
 * \brief Macro for not changing the rotator speed with move() function
 */
#define ROT_SPEED_NOCHANGE (-1)


/**
 * \brief Rotator Level Settings
 *
 * Various operating levels supported by a rotator.\n
 * \c STRING used in rotctl
 *
 * \sa rot_parse_level(), rot_strlevel()
 */
enum rot_level_e {
    ROT_LEVEL_NONE =        0,              /*!< '' -- No Level */
    ROT_LEVEL_SPEED =       (1 << 0),       /*!< \c SPEED -- Rotation speed, arg int (1-100) */
    ROT_LEVEL_63 =          CONSTANT_64BIT_FLAG(63),      /*!< \c Future use, last level */
};


//! @cond Doxygen_Suppress
#define ROT_LEVEL_FLOAT_LIST (0)

#define ROT_LEVEL_READONLY_LIST (0)

#define ROT_LEVEL_IS_FLOAT(l) ((l)&ROT_LEVEL_FLOAT_LIST)
#define ROT_LEVEL_SET(l) ((l)&~ROT_LEVEL_READONLY_LIST)
//! @endcond


/**
 * \brief Rotator Parameters
 *
 * Parameters are settings that are not related to core rotator functionality (= antenna rotation).\n
 * \c STRING used in rotctl
 *
 * \sa rot_parse_parm(), rot_strparm()
 */
enum rot_parm_e {
    ROT_PARM_NONE =         0,          /*!< '' -- No Parm */
};


//! @cond Doxygen_Suppress
#define ROT_PARM_FLOAT_LIST (0)
#define ROT_PARM_READONLY_LIST (0)

#define ROT_PARM_IS_FLOAT(l) ((l)&ROT_PARM_FLOAT_LIST)
#define ROT_PARM_SET(l) ((l)&~ROT_PARM_READONLY_LIST)
//! @endcond


/**
 * \brief Rotator Function Settings
 *
 * Various operating functions supported by a rotator.\n
 * \c STRING used in rotctl/rotctld
 *
 * \sa rot_parse_func(), rot_strfunc()
 */
#define ROT_FUNC_NONE       0                          /*!< '' -- No Function */
#ifndef SWIGLUAHIDE
/* Hide the top 32 bits from the old Lua binding as they can't be represented */
#define ROT_FUNC_BIT63      CONSTANT_64BIT_FLAG (63)   /*!< \c available for future ROT_FUNC items */
/* 63 is this highest bit number that can be used */
#endif


/* Basic rot type, can store some useful info about different rotators. Each
 * lib must be able to populate this structure, so we can make useful
 * enquiries about capabilities.
 */

/**
 * Rotator Caps
 * \struct rot_caps
 * \brief Rotator data structure.
 *
 * The main idea of this struct is that it will be defined by the backend
 * rotator driver, and will remain readonly for the application.  Fields that
 * need to be modifiable by the application are copied into the struct
 * rot_state, which is a kind of private of the ROT instance.
 *
 * This way, you can have several rigs running within the same application,
 * sharing the struct rot_caps of the backend, while keeping their own
 * customized data.
 *
 * mdblack: Careful moving fields around, as the backends depend on it when
 *       initializing their caps in shared libraries and dlls.
 */

//! @cond Doxygen_Suppress
#define ROT_MODEL(arg) .rot_model=arg,.macro_name=#arg
struct rot_caps {
    rot_model_t rot_model;                      /*!< Rotator model. */
    const char *model_name;                     /*!< Model name. */
    const char *mfg_name;                       /*!< Manufacturer. */
    const char *version;                        /*!< Driver version. */
    const char *copyright;                      /*!< Copyright info. */
    enum rig_status_e status;                   /*!< Driver status. */

    int rot_type;                               /*!< Rotator type. */
    enum rig_port_e port_type;                  /*!< Type of communication port. */

    int serial_rate_min;                        /*!< Minimal serial speed. */
    int serial_rate_max;                        /*!< Maximal serial speed. */
    int serial_data_bits;                       /*!< Number of data bits. */
    int serial_stop_bits;                       /*!< Number of stop bits. */
    enum serial_parity_e serial_parity;         /*!< Parity. */
    enum serial_handshake_e serial_handshake;   /*!< Handshake. */

    int write_delay;                            /*!< Write delay. */
    int post_write_delay;                       /*!< Post-write delay. */
    int timeout;                                /*!< Timeout. */
    int retry;                                  /*!< Number of retry if command fails. */

    setting_t has_get_func;     /*!< List of get functions */
    setting_t has_set_func;     /*!< List of set functions */
    setting_t has_get_level;    /*!< List of get level */
    setting_t has_set_level;    /*!< List of set level */
    setting_t has_get_parm;     /*!< List of get parm */
    setting_t has_set_parm;     /*!< List of set parm */

    gran_t level_gran[RIG_SETTING_MAX]; /*!< level granularity (i.e. steps) */
    gran_t parm_gran[RIG_SETTING_MAX];  /*!< parm granularity (i.e. steps) */

    const struct confparams *extparms;  /*!< Extension parm list, \sa ext.c */
    const struct confparams *extlevels; /*!< Extension level list, \sa ext.c */
    const struct confparams *extfuncs; /*!< Extension func list, \sa ext.c */
    int *ext_tokens;                    /*!< Extension token list */

    /*
     * Movement range, az is relative to North
     * negative values allowed for overlap
     */
    azimuth_t min_az;                           /*!< Lower limit for azimuth (relative to North). */
    azimuth_t max_az;                           /*!< Upper limit for azimuth (relative to North). */
    elevation_t
    min_el;                                     /*!< Lower limit for elevation. */
    elevation_t
    max_el;                                     /*!< Upper limit for elevation. */


    const struct confparams *cfgparams;         /*!< Configuration parameters. */
    const rig_ptr_t priv;                       /*!< Private data. */

    /*
     * Rot Admin API
     *
     */

    int (*rot_init)(ROT *rot);
    int (*rot_cleanup)(ROT *rot);
    int (*rot_open)(ROT *rot);
    int (*rot_close)(ROT *rot);

    int (*set_conf)(ROT *rot, token_t token, const char *val);
    int (*get_conf)(ROT *rot, token_t token, char *val);

    /*
     *  General API commands, from most primitive to least.. :()
     *  List Set/Get functions pairs
     */

    int (*set_position)(ROT *rot, azimuth_t azimuth, elevation_t elevation);
    int (*get_position)(ROT *rot, azimuth_t *azimuth, elevation_t *elevation);

    int (*stop)(ROT *rot);
    int (*park)(ROT *rot);
    int (*reset)(ROT *rot, rot_reset_t reset);
    int (*move)(ROT *rot, int direction, int speed);

    /* get firmware info, etc. */
    const char * (*get_info)(ROT *rot);

    int (*set_level)(ROT *rot, setting_t level, value_t val);
    int (*get_level)(ROT *rot, setting_t level, value_t *val);

    int (*set_func)(ROT *rot, setting_t func, int status);
    int (*get_func)(ROT *rot, setting_t func, int *status);

    int (*set_parm)(ROT *rot, setting_t parm, value_t val);
    int (*get_parm)(ROT *rot, setting_t parm, value_t *val);

    int (*set_ext_level)(ROT *rot, token_t token, value_t val);
    int (*get_ext_level)(ROT *rot, token_t token, value_t *val);

    int (*set_ext_func)(ROT *rot, token_t token, int status);
    int (*get_ext_func)(ROT *rot, token_t token, int *status);

    int (*set_ext_parm)(ROT *rot, token_t token, value_t val);
    int (*get_ext_parm)(ROT *rot, token_t token, value_t *val);

    const char *macro_name;                     /*!< Macro name. */

    rot_status_t status_caps;                   /*!< Supported status flags */

    rot_status_t (*get_status)(ROT *rot);
    /* more to come... */
};
//! @endcond


/**
 * Rotator state
 * \struct rot_state
 * \brief Live data and customized fields.
 *
 * This struct contains live data, as well as a copy of capability fields
 * that may be updated (ie. customized)
 *
 * It is fine to move fields around, as this kind of struct should
 * not be initialized like caps are.
 */
struct rot_state {
    /*
     * overridable fields
     */
    azimuth_t min_az;       /*!< Lower limit for azimuth (overridable). */
    azimuth_t max_az;       /*!< Upper limit for azimuth (overridable). */
    elevation_t min_el;     /*!< Lower limit for elevation (overridable). */
    elevation_t max_el;     /*!< Upper limit for elevation (overridable). */
    int south_zero;         /*!< South is zero degrees */
    azimuth_t az_offset;    /*!< Offset to be applied to azimuth */
    elevation_t el_offset;  /*!< Offset to be applied to elevation */

    setting_t has_get_func;     /*!< List of get functions */
    setting_t has_set_func;     /*!< List of set functions */
    setting_t has_get_level;    /*!< List of get level */
    setting_t has_set_level;    /*!< List of set level */
    setting_t has_get_parm;     /*!< List of get parm */
    setting_t has_set_parm;     /*!< List of set parm */

    gran_t level_gran[RIG_SETTING_MAX]; /*!< level granularity */
    gran_t parm_gran[RIG_SETTING_MAX];  /*!< parm granularity */

    /*
     * non overridable fields, internal use
     */
    hamlib_port_t rotport;  /*!< Rotator port (internal use). */

    int comm_state;         /*!< Comm port state, opened/closed. */
    rig_ptr_t priv;         /*!< Pointer to private rotator state data. */
    rig_ptr_t obj;          /*!< Internal use by hamlib++ for event handling. */

    int current_speed;      /*!< Current speed 1-100, to be used when no change to speed is requested */
    /* etc... */
};


/**
 * Rotator structure
 * \struct s_rot
 * \brief This is the master data structure,
 * acting as a handle for the controlled rotator.
 *
 * This is the master data structure, acting as a handle for the controlled
 * rotator. A pointer to this structure is returned by the rot_init() API
 * function and is passed as a parameter to every rotator specific API call.
 *
 * \sa rot_init(), rot_caps(), rot_state()
 */
struct s_rot {
    struct rot_caps *caps;      /*!< Rotator caps. */
    struct rot_state state;     /*!< Rotator state. */
};


//! @cond Doxygen_Suppress
/* --------------- API function prototypes -----------------*/

extern HAMLIB_EXPORT(ROT *)
rot_init HAMLIB_PARAMS((rot_model_t rot_model));

extern HAMLIB_EXPORT(int)
rot_open HAMLIB_PARAMS((ROT *rot));

extern HAMLIB_EXPORT(int)
rot_close HAMLIB_PARAMS((ROT *rot));

extern HAMLIB_EXPORT(int)
rot_cleanup HAMLIB_PARAMS((ROT *rot));

extern HAMLIB_EXPORT(int)
rot_set_conf HAMLIB_PARAMS((ROT *rot,
                            token_t token,
                            const char *val));
extern HAMLIB_EXPORT(int)
rot_get_conf HAMLIB_PARAMS((ROT *rot,
                            token_t token,
                            char *val));

/*
 *  General API commands, from most primitive to least.. )
 *  List Set/Get functions pairs
 */
extern HAMLIB_EXPORT(int)
rot_set_position HAMLIB_PARAMS((ROT *rot,
                                azimuth_t azimuth,
                                elevation_t elevation));
extern HAMLIB_EXPORT(int)
rot_get_position HAMLIB_PARAMS((ROT *rot,
                                azimuth_t *azimuth,
                                elevation_t *elevation));

extern HAMLIB_EXPORT(int)
rot_stop HAMLIB_PARAMS((ROT *rot));

extern HAMLIB_EXPORT(int)
rot_park HAMLIB_PARAMS((ROT *rot));

extern HAMLIB_EXPORT(int)
rot_reset HAMLIB_PARAMS((ROT *rot,
                         rot_reset_t reset));

extern HAMLIB_EXPORT(int)
rot_move HAMLIB_PARAMS((ROT *rot,
                        int direction,
                        int speed));

extern HAMLIB_EXPORT(setting_t)
rot_has_get_level HAMLIB_PARAMS((ROT *rot,
                                 setting_t level));
extern HAMLIB_EXPORT(setting_t)
rot_has_set_level HAMLIB_PARAMS((ROT *rot,
                                 setting_t level));

extern HAMLIB_EXPORT(setting_t)
rot_has_get_parm HAMLIB_PARAMS((ROT *rot,
                                setting_t parm));
extern HAMLIB_EXPORT(setting_t)
rot_has_set_parm HAMLIB_PARAMS((ROT *rot,
                                setting_t parm));

extern HAMLIB_EXPORT(setting_t)
rot_has_get_func HAMLIB_PARAMS((ROT *rot,
                                setting_t func));
extern HAMLIB_EXPORT(setting_t)
rot_has_set_func HAMLIB_PARAMS((ROT *rot,
                                setting_t func));

extern HAMLIB_EXPORT(int)
rot_set_func HAMLIB_PARAMS((ROT *rot,
                            setting_t func,
                            int status));
extern HAMLIB_EXPORT(int)
rot_get_func HAMLIB_PARAMS((ROT *rot,
                            setting_t func,
                            int *status));

extern HAMLIB_EXPORT(int)
rot_set_level HAMLIB_PARAMS((ROT *rig,
                             setting_t level,
                             value_t val));
extern HAMLIB_EXPORT(int)
rot_get_level HAMLIB_PARAMS((ROT *rig,
                             setting_t level,
                             value_t *val));

extern HAMLIB_EXPORT(int)
rot_set_parm HAMLIB_PARAMS((ROT *rig,
                            setting_t parm,
                            value_t val));
extern HAMLIB_EXPORT(int)
rot_get_parm HAMLIB_PARAMS((ROT *rig,
                            setting_t parm,
                            value_t *val));

extern HAMLIB_EXPORT(int)
rot_set_ext_level HAMLIB_PARAMS((ROT *rig,
                                 token_t token,
                                 value_t val));
extern HAMLIB_EXPORT(int)
rot_get_ext_level HAMLIB_PARAMS((ROT *rig,
                                 token_t token,
                                 value_t *val));

extern HAMLIB_EXPORT(int)
rot_set_ext_func HAMLIB_PARAMS((ROT *rig,
                                 token_t token,
                                 int status));
extern HAMLIB_EXPORT(int)
rot_get_ext_func HAMLIB_PARAMS((ROT *rig,
                                 token_t token,
                                 int *status));

extern HAMLIB_EXPORT(int)
rot_set_ext_parm HAMLIB_PARAMS((ROT *rig,
                                token_t token,
                                value_t val));
extern HAMLIB_EXPORT(int)
rot_get_ext_parm HAMLIB_PARAMS((ROT *rig,
                                token_t token,
                                value_t *val));

extern HAMLIB_EXPORT(const char *)
rot_get_info HAMLIB_PARAMS((ROT *rot));

extern HAMLIB_EXPORT(int)
rot_register HAMLIB_PARAMS((const struct rot_caps *caps));

extern HAMLIB_EXPORT(int)
rot_unregister HAMLIB_PARAMS((rot_model_t rot_model));

extern HAMLIB_EXPORT(int)
rot_list_foreach HAMLIB_PARAMS((int (*cfunc)(const struct rot_caps *,
                                             rig_ptr_t),
                                rig_ptr_t data));

extern HAMLIB_EXPORT(int)
rot_load_backend HAMLIB_PARAMS((const char *be_name));

extern HAMLIB_EXPORT(int)
rot_check_backend HAMLIB_PARAMS((rot_model_t rot_model));

extern HAMLIB_EXPORT(int)
rot_load_all_backends HAMLIB_PARAMS((void));

extern HAMLIB_EXPORT(rot_model_t)
rot_probe_all HAMLIB_PARAMS((hamlib_port_t *p));

extern HAMLIB_EXPORT(int)
rot_token_foreach HAMLIB_PARAMS((ROT *rot,
                                 int (*cfunc)(const struct confparams *,
                                              rig_ptr_t),
                                 rig_ptr_t data));

extern HAMLIB_EXPORT(const struct confparams *)
rot_confparam_lookup HAMLIB_PARAMS((ROT *rot,
                                   const char *name));

extern HAMLIB_EXPORT(token_t)
rot_token_lookup HAMLIB_PARAMS((ROT *rot,
                                const char *name));

extern HAMLIB_EXPORT(int)
rot_ext_func_foreach HAMLIB_PARAMS((ROT *rot,
                                     int (*cfunc)(ROT *,
                                                  const struct confparams *,
                                                  rig_ptr_t),
                                     rig_ptr_t data));
extern HAMLIB_EXPORT(int)
rot_ext_level_foreach HAMLIB_PARAMS((ROT *rot,
                                     int (*cfunc)(ROT *,
                                                  const struct confparams *,
                                                  rig_ptr_t),
                                     rig_ptr_t data));
extern HAMLIB_EXPORT(int)
rot_ext_parm_foreach HAMLIB_PARAMS((ROT *rot,
                                    int (*cfunc)(ROT *,
                                                 const struct confparams *,
                                                 rig_ptr_t),
                                    rig_ptr_t data));

extern HAMLIB_EXPORT(const struct confparams *)
rot_ext_lookup HAMLIB_PARAMS((ROT *rot,
                              const char *name));

extern HAMLIB_EXPORT(const struct confparams *)
rot_ext_lookup_tok HAMLIB_PARAMS((ROT *rot,
                                  token_t token));
extern HAMLIB_EXPORT(token_t)
rot_ext_token_lookup HAMLIB_PARAMS((ROT *rot,
                                    const char *name));

extern HAMLIB_EXPORT(const struct rot_caps *)
rot_get_caps HAMLIB_PARAMS((rot_model_t rot_model));

extern HAMLIB_EXPORT(int)
qrb HAMLIB_PARAMS((double lon1,
                   double lat1,
                   double lon2,
                   double lat2,
                   double *distance,
                   double *azimuth));

extern HAMLIB_EXPORT(double)
distance_long_path HAMLIB_PARAMS((double distance));

extern HAMLIB_EXPORT(double)
azimuth_long_path HAMLIB_PARAMS((double azimuth));

extern HAMLIB_EXPORT(int)
longlat2locator HAMLIB_PARAMS((double longitude,
                               double latitude,
                               char *locator_res,
                               int pair_count));

extern HAMLIB_EXPORT(int)
locator2longlat HAMLIB_PARAMS((double *longitude,
                               double *latitude,
                               const char *locator));

extern HAMLIB_EXPORT(double)
dms2dec HAMLIB_PARAMS((int degrees,
                       int minutes,
                       double seconds,
                       int sw));

extern HAMLIB_EXPORT(int)
dec2dms HAMLIB_PARAMS((double dec,
                       int *degrees,
                       int *minutes,
                       double *seconds,
                       int *sw));

extern HAMLIB_EXPORT(int)
dec2dmmm HAMLIB_PARAMS((double dec,
                        int *degrees,
                        double *minutes,
                        int *sw));

extern HAMLIB_EXPORT(double)
dmmm2dec HAMLIB_PARAMS((int degrees,
                        double minutes,
                        double seconds,
                        int sw));

//! @endcond

/**
 *  \def rot_debug
 *  \brief Convenience definition for debug level.
 *
 *  This is just as convenience definition of the rotator debug level,
 *  and is the same as for the rig debug level.
 *
 *  \sa rig_debug()
 */
#define rot_debug rig_debug

__END_DECLS

#endif /* _ROTATOR_H */

/** @} */
