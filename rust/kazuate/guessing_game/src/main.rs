//enum IpAddrKind {
//    V4,
//    V6,
//}

//fn sub() {
//    let four = IpAddrKind::V4;
//    println!("Hello Sub!!");
//}

struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

pub trait TUser {
    fn get_username(&self) -> String;
    fn get_email(&self) -> String;
    fn get_sign_in_count(&self) -> u64;
    fn get_active(&self) -> bool;

}


fn 出力する<'s>(msg: &'s String) {
    println!("{}", msg);
}

fn main() {
    let message = String::from("こんにちは");
    出力する(&message);
    let val = 20;
    func(&val);

    let user1 = User {
        username: String::from("miyuki"),
        email: String::from("hogehoge@example.com"),
        sign_in_count: 0,
        active: true,
    };

}
