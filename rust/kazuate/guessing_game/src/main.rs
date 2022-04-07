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

struct Result(bool, i32);


fn func<'s>(val: &'s i32) -> &'s i32 {
    val
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
