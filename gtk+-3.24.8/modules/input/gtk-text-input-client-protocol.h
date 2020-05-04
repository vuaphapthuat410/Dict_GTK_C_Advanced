/* Generated by wayland-scanner 1.16.0 */

#ifndef GTK_TEXT_INPUT_CLIENT_PROTOCOL_H
#define GTK_TEXT_INPUT_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_gtk_text_input The gtk_text_input protocol
 * @section page_ifaces_gtk_text_input Interfaces
 * - @subpage page_iface_gtk_text_input - text input
 * - @subpage page_iface_gtk_text_input_manager - text input manager
 * @section page_copyright_gtk_text_input Copyright
 * <pre>
 *
 * Copyright © 2012, 2013 Intel Corporation
 * Copyright © 2015, 2016 Jan Arne Petersen
 *
 * Permission to use, copy, modify, distribute, and sell this
 * software and its documentation for any purpose is hereby granted
 * without fee, provided that the above copyright notice appear in
 * all copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * the copyright holders not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 * </pre>
 */
struct gtk_text_input;
struct gtk_text_input_manager;
struct wl_seat;
struct wl_surface;

/**
 * @page page_iface_gtk_text_input gtk_text_input
 * @section page_iface_gtk_text_input_desc Description
 *
 * The gtk_text_input interface represents text input and input methods
 * associated with a seat. It provides enter/leave events to follow the
 * text input focus for a seat.
 *
 * Requests are used to enable/disable the text-input object and set
 * state information like surrounding and selected text or the content type.
 * The information about the entered text is sent to the text-input object
 * via the pre-edit and commit_string events. Using this interface removes
 * the need for applications to directly process hardware key events and
 * compose text out of them.
 *
 * Text is valid UTF-8 encoded, indices and lengths are in bytes. Indices
 * have to always point to the first byte of an UTF-8 encoded code point.
 * Lengths are not allowed to contain just a part of an UTF-8 encoded code
 * point.
 *
 * Focus moving throughout surfaces will result in the emission of
 * gtk_text_input.enter and gtk_text_input.leave events. The focused
 * surface must perform gtk_text_input.enable and
 * gtk_text_input.disable requests as the keyboard focus moves across
 * editable and non-editable elements of the UI. Those two requests are not
 * expected to be paired with each other, the compositor must be able to
 * handle consecutive series of the same request.
 *
 * State is sent by the state requests (set_surrounding_text,
 * set_content_type and set_cursor_rectangle) and a commit request.
 * After an enter event or disable request all state information is
 * invalidated and needs to be resent by the client.
 *
 * This protocol defines requests and events necessary for regular clients
 * to communicate with an input method. The gtk_input_method protocol
 * defines the interfaces necessary to implement standalone input methods.
 * If a compositor implements both interfaces, it will be the arbiter of the
 * communication between both.
 *
 * Warning! The protocol described in this file is experimental and
 * backward incompatible changes may be made. Backward compatible changes
 * may be added together with the corresponding interface version bump.
 * Backward incompatible changes are done by bumping the version number in
 * the protocol and interface names and resetting the interface version.
 * Once the protocol is to be declared stable, the 'z' prefix and the
 * version number in the protocol and interface names are removed and the
 * interface version number is reset.
 * @section page_iface_gtk_text_input_api API
 * See @ref iface_gtk_text_input.
 */
/**
 * @defgroup iface_gtk_text_input The gtk_text_input interface
 *
 * The gtk_text_input interface represents text input and input methods
 * associated with a seat. It provides enter/leave events to follow the
 * text input focus for a seat.
 *
 * Requests are used to enable/disable the text-input object and set
 * state information like surrounding and selected text or the content type.
 * The information about the entered text is sent to the text-input object
 * via the pre-edit and commit_string events. Using this interface removes
 * the need for applications to directly process hardware key events and
 * compose text out of them.
 *
 * Text is valid UTF-8 encoded, indices and lengths are in bytes. Indices
 * have to always point to the first byte of an UTF-8 encoded code point.
 * Lengths are not allowed to contain just a part of an UTF-8 encoded code
 * point.
 *
 * Focus moving throughout surfaces will result in the emission of
 * gtk_text_input.enter and gtk_text_input.leave events. The focused
 * surface must perform gtk_text_input.enable and
 * gtk_text_input.disable requests as the keyboard focus moves across
 * editable and non-editable elements of the UI. Those two requests are not
 * expected to be paired with each other, the compositor must be able to
 * handle consecutive series of the same request.
 *
 * State is sent by the state requests (set_surrounding_text,
 * set_content_type and set_cursor_rectangle) and a commit request.
 * After an enter event or disable request all state information is
 * invalidated and needs to be resent by the client.
 *
 * This protocol defines requests and events necessary for regular clients
 * to communicate with an input method. The gtk_input_method protocol
 * defines the interfaces necessary to implement standalone input methods.
 * If a compositor implements both interfaces, it will be the arbiter of the
 * communication between both.
 *
 * Warning! The protocol described in this file is experimental and
 * backward incompatible changes may be made. Backward compatible changes
 * may be added together with the corresponding interface version bump.
 * Backward incompatible changes are done by bumping the version number in
 * the protocol and interface names and resetting the interface version.
 * Once the protocol is to be declared stable, the 'z' prefix and the
 * version number in the protocol and interface names are removed and the
 * interface version number is reset.
 */
extern const struct wl_interface gtk_text_input_interface;
/**
 * @page page_iface_gtk_text_input_manager gtk_text_input_manager
 * @section page_iface_gtk_text_input_manager_desc Description
 *
 * A factory for text-input objects. This object is a global singleton.
 * @section page_iface_gtk_text_input_manager_api API
 * See @ref iface_gtk_text_input_manager.
 */
/**
 * @defgroup iface_gtk_text_input_manager The gtk_text_input_manager interface
 *
 * A factory for text-input objects. This object is a global singleton.
 */
extern const struct wl_interface gtk_text_input_manager_interface;

#ifndef GTK_TEXT_INPUT_ENABLE_FLAGS_ENUM
#define GTK_TEXT_INPUT_ENABLE_FLAGS_ENUM
/**
 * @ingroup iface_gtk_text_input
 * enable flags
 *
 * Content hint is a bitmask to allow to modify the behavior of the text
 * input.
 */
enum gtk_text_input_enable_flags {
	/**
	 * no special behaviour
	 */
	GTK_TEXT_INPUT_ENABLE_FLAGS_NONE = 0x0,
	/**
	 * hints that the UI is capable of showing pre-edit text
	 */
	GTK_TEXT_INPUT_ENABLE_FLAGS_CAN_SHOW_PREEDIT = 0x1,
	/**
	 * requests toggling input panel (eg. on-screen keyboard)
	 */
	GTK_TEXT_INPUT_ENABLE_FLAGS_TOGGLE_INPUT_PANEL = 0x2,
};
#endif /* GTK_TEXT_INPUT_ENABLE_FLAGS_ENUM */

#ifndef GTK_TEXT_INPUT_CONTENT_HINT_ENUM
#define GTK_TEXT_INPUT_CONTENT_HINT_ENUM
/**
 * @ingroup iface_gtk_text_input
 * content hint
 *
 * Content hint is a bitmask to allow to modify the behavior of the text
 * input.
 */
enum gtk_text_input_content_hint {
	/**
	 * no special behaviour
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_NONE = 0x0,
	/**
	 * suggest word completions
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_COMPLETION = 0x1,
	/**
	 * suggest word corrections
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_SPELLCHECK = 0x2,
	/**
	 * switch to uppercase letters at the start of a sentence
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_AUTO_CAPITALIZATION = 0x4,
	/**
	 * prefer lowercase letters
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_LOWERCASE = 0x8,
	/**
	 * prefer uppercase letters
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_UPPERCASE = 0x10,
	/**
	 * prefer casing for titles and headings (can be language dependent)
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_TITLECASE = 0x20,
	/**
	 * characters should be hidden
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_HIDDEN_TEXT = 0x40,
	/**
	 * typed text should not be stored
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_SENSITIVE_DATA = 0x80,
	/**
	 * just latin characters should be entered
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_LATIN = 0x100,
	/**
	 * the text input is multiline
	 */
	GTK_TEXT_INPUT_CONTENT_HINT_MULTILINE = 0x200,
};
#endif /* GTK_TEXT_INPUT_CONTENT_HINT_ENUM */

#ifndef GTK_TEXT_INPUT_CONTENT_PURPOSE_ENUM
#define GTK_TEXT_INPUT_CONTENT_PURPOSE_ENUM
/**
 * @ingroup iface_gtk_text_input
 * content purpose
 *
 * The content purpose allows to specify the primary purpose of a text
 * input.
 *
 * This allows an input method to show special purpose input panels with
 * extra characters or to disallow some characters.
 */
enum gtk_text_input_content_purpose {
	/**
	 * default input, allowing all characters
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_NORMAL = 0,
	/**
	 * allow only alphabetic characters
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_ALPHA = 1,
	/**
	 * allow only digits
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_DIGITS = 2,
	/**
	 * input a number (including decimal separator and sign)
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_NUMBER = 3,
	/**
	 * input a phone number
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_PHONE = 4,
	/**
	 * input an URL
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_URL = 5,
	/**
	 * input an email address
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_EMAIL = 6,
	/**
	 * input a name of a person
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_NAME = 7,
	/**
	 * input a password (combine with password or sensitive_data hint)
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_PASSWORD = 8,
	/**
	 * input is a numeric password (combine with password or sensitive_data hint)
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_PIN = 9,
	/**
	 * input a date
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_DATE = 10,
	/**
	 * input a time
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_TIME = 11,
	/**
	 * input a date and time
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_DATETIME = 12,
	/**
	 * input for a terminal
	 */
	GTK_TEXT_INPUT_CONTENT_PURPOSE_TERMINAL = 13,
};
#endif /* GTK_TEXT_INPUT_CONTENT_PURPOSE_ENUM */

/**
 * @ingroup iface_gtk_text_input
 * @struct gtk_text_input_listener
 */
struct gtk_text_input_listener {
	/**
	 * enter event
	 *
	 * Notification that this seat's text-input focus is on a certain
	 * surface.
	 *
	 * When the seat has the keyboard capability the text-input focus
	 * follows the keyboard focus.
	 * @param serial serial
	 */
	void (*enter)(void *data,
		      struct gtk_text_input *gtk_text_input,
		      uint32_t serial,
		      struct wl_surface *surface);
	/**
	 * leave event
	 *
	 * Notification that this seat's text-input focus is no longer on
	 * a certain surface. The client should reset any preedit string
	 * previously set.
	 *
	 * The leave notification is sent before the enter notification for
	 * the new focus.
	 *
	 * When the seat has the keyboard capability the text-input focus
	 * follows the keyboard focus.
	 */
	void (*leave)(void *data,
		      struct gtk_text_input *gtk_text_input,
		      uint32_t serial,
		      struct wl_surface *surface);
	/**
	 * pre-edit
	 *
	 * Notify when a new composing text (pre-edit) should be set
	 * around the current cursor position. Any previously set composing
	 * text should be removed.
	 */
	void (*preedit_string)(void *data,
			       struct gtk_text_input *gtk_text_input,
			       const char *text,
			       uint32_t cursor);
	/**
	 * text commit
	 *
	 * Notify when text should be inserted into the editor widget.
	 * The text to commit could be either just a single character after
	 * a key press or the result of some composing (pre-edit).
	 *
	 * The text argument could be also null if some text is removed
	 * (see gtk_text_input.delete_surrounding_text).
	 *
	 * Any previously set composing text should be removed.
	 */
	void (*commit_string)(void *data,
			      struct gtk_text_input *gtk_text_input,
			      const char *text);
	/**
	 * delete surrounding text
	 *
	 * Notify when the text around the current cursor position should
	 * be deleted. Before_length and after_length is the length (in
	 * bytes) of text before and after the current cursor position
	 * (excluding the selection) to delete.
	 *
	 * This event should be handled as part of a following
	 * commit_string or preedit_string event.
	 * @param before_length length of text before current cursor position
	 * @param after_length length of text after current cursor position
	 */
	void (*delete_surrounding_text)(void *data,
					struct gtk_text_input *gtk_text_input,
					uint32_t before_length,
					uint32_t after_length);
};

/**
 * @ingroup iface_gtk_text_input
 */
static inline int
gtk_text_input_add_listener(struct gtk_text_input *gtk_text_input,
			    const struct gtk_text_input_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) gtk_text_input,
				     (void (**)(void)) listener, data);
}

#define GTK_TEXT_INPUT_DESTROY 0
#define GTK_TEXT_INPUT_ENABLE 1
#define GTK_TEXT_INPUT_DISABLE 2
#define GTK_TEXT_INPUT_SET_SURROUNDING_TEXT 3
#define GTK_TEXT_INPUT_SET_CONTENT_TYPE 4
#define GTK_TEXT_INPUT_SET_CURSOR_RECTANGLE 5
#define GTK_TEXT_INPUT_COMMIT 6

/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_ENTER_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_LEAVE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_PREEDIT_STRING_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_COMMIT_STRING_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_DELETE_SURROUNDING_TEXT_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_DESTROY_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_ENABLE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_DISABLE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_SET_SURROUNDING_TEXT_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_SET_CONTENT_TYPE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_SET_CURSOR_RECTANGLE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input
 */
#define GTK_TEXT_INPUT_COMMIT_SINCE_VERSION 1

/** @ingroup iface_gtk_text_input */
static inline void
gtk_text_input_set_user_data(struct gtk_text_input *gtk_text_input, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) gtk_text_input, user_data);
}

/** @ingroup iface_gtk_text_input */
static inline void *
gtk_text_input_get_user_data(struct gtk_text_input *gtk_text_input)
{
	return wl_proxy_get_user_data((struct wl_proxy *) gtk_text_input);
}

static inline uint32_t
gtk_text_input_get_version(struct gtk_text_input *gtk_text_input)
{
	return wl_proxy_get_version((struct wl_proxy *) gtk_text_input);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Destroy the wp_text_input object. Also disables all surfaces enabled
 * through this wp_text_input object
 */
static inline void
gtk_text_input_destroy(struct gtk_text_input *gtk_text_input)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) gtk_text_input);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Requests text input on a surface. The serial provided must be the one
 * received on gtk_text_input.enter.
 */
static inline void
gtk_text_input_enable(struct gtk_text_input *gtk_text_input, uint32_t serial, uint32_t show_input_panel)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_ENABLE, serial, show_input_panel);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Explicitly disable text input in a surface (typically when there is no
 * focus on any text entry inside the surface).
 */
static inline void
gtk_text_input_disable(struct gtk_text_input *gtk_text_input)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_DISABLE);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Sets the plain surrounding text around the input position. Text is
 * UTF-8 encoded. Cursor is the byte offset within the surrounding text.
 * Anchor is the byte offset of the selection anchor within the
 * surrounding text. If there is no selected text, anchor is the same as
 * cursor.
 *
 * Make sure to always send some text before and after the cursor
 * except when the cursor is at the beginning or end of text.
 *
 * When there was a configure_surrounding_text event take the
 * before_cursor and after_cursor arguments into account for picking how
 * much surrounding text to send.
 *
 * There is a maximum length of wayland messages so text can not be
 * longer than 4000 bytes.
 */
static inline void
gtk_text_input_set_surrounding_text(struct gtk_text_input *gtk_text_input, const char *text, int32_t cursor, int32_t anchor)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_SET_SURROUNDING_TEXT, text, cursor, anchor);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Sets the content purpose and content hint. While the purpose is the
 * basic purpose of an input field, the hint flags allow to modify some
 * of the behavior.
 *
 * When no content type is explicitly set, a normal content purpose with
 * none hint should be assumed.
 */
static inline void
gtk_text_input_set_content_type(struct gtk_text_input *gtk_text_input, uint32_t hint, uint32_t purpose)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_SET_CONTENT_TYPE, hint, purpose);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Sets the cursor outline as a x, y, width, height rectangle in surface
 * local coordinates.
 *
 * Allows the compositor to put a window with word suggestions near the
 * cursor.
 */
static inline void
gtk_text_input_set_cursor_rectangle(struct gtk_text_input *gtk_text_input, int32_t x, int32_t y, int32_t width, int32_t height)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_SET_CURSOR_RECTANGLE, x, y, width, height);
}

/**
 * @ingroup iface_gtk_text_input
 *
 * Allows to atomically send state updates from client. The previous
 * set_surrounding_text, set_content_type and set_cursor_rectangle
 * become effective after this call.
 *
 * Serial should be set to the serial from the last wp_text_input.enter
 * event.
 *
 * To make sure to not receive outdated input method events after a
 * state update, wl_display_sync() should be called after making this
 * request.
 */
static inline void
gtk_text_input_commit(struct gtk_text_input *gtk_text_input)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input,
			 GTK_TEXT_INPUT_COMMIT);
}

#define GTK_TEXT_INPUT_MANAGER_DESTROY 0
#define GTK_TEXT_INPUT_MANAGER_GET_TEXT_INPUT 1


/**
 * @ingroup iface_gtk_text_input_manager
 */
#define GTK_TEXT_INPUT_MANAGER_DESTROY_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_text_input_manager
 */
#define GTK_TEXT_INPUT_MANAGER_GET_TEXT_INPUT_SINCE_VERSION 1

/** @ingroup iface_gtk_text_input_manager */
static inline void
gtk_text_input_manager_set_user_data(struct gtk_text_input_manager *gtk_text_input_manager, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) gtk_text_input_manager, user_data);
}

/** @ingroup iface_gtk_text_input_manager */
static inline void *
gtk_text_input_manager_get_user_data(struct gtk_text_input_manager *gtk_text_input_manager)
{
	return wl_proxy_get_user_data((struct wl_proxy *) gtk_text_input_manager);
}

static inline uint32_t
gtk_text_input_manager_get_version(struct gtk_text_input_manager *gtk_text_input_manager)
{
	return wl_proxy_get_version((struct wl_proxy *) gtk_text_input_manager);
}

/**
 * @ingroup iface_gtk_text_input_manager
 *
 * Destroy the wp_text_input_manager object.
 */
static inline void
gtk_text_input_manager_destroy(struct gtk_text_input_manager *gtk_text_input_manager)
{
	wl_proxy_marshal((struct wl_proxy *) gtk_text_input_manager,
			 GTK_TEXT_INPUT_MANAGER_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) gtk_text_input_manager);
}

/**
 * @ingroup iface_gtk_text_input_manager
 *
 * Creates a new text-input object for a given seat.
 */
static inline struct gtk_text_input *
gtk_text_input_manager_get_text_input(struct gtk_text_input_manager *gtk_text_input_manager, struct wl_seat *seat)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_constructor((struct wl_proxy *) gtk_text_input_manager,
			 GTK_TEXT_INPUT_MANAGER_GET_TEXT_INPUT, &gtk_text_input_interface, NULL, seat);

	return (struct gtk_text_input *) id;
}

#ifdef  __cplusplus
}
#endif

#endif