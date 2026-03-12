use rfd::{MessageDialog, MessageLevel, MessageButtons};

pub fn msg_info(title: &str, message: &str) {
    MessageDialog::new()
        .set_title(title)
        .set_description(message)
        .set_level(MessageLevel::Info)
        .set_buttons(MessageButtons::Ok)
        .show();
}

pub fn msg_warn(title: &str, message: &str) {
    MessageDialog::new()
        .set_title(title)
        .set_description(message)
        .set_level(MessageLevel::Warning)
        .set_buttons(MessageButtons::Ok)
        .show();
}

pub fn msg_error(title: &str, message: &str) {
    MessageDialog::new()
        .set_title(title)
        .set_description(message)
        .set_level(MessageLevel::Error)
        .set_buttons(MessageButtons::Ok)
        .show();
}