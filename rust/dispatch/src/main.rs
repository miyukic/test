
pub struct Human {
}

pub struct Dog {
}

pub trait Creature {
    fn voice(&self);
}

impl Creature for Human {
    fn voice(&self) {
        println!("こんにちは");
    }
}

impl Creature for Dog {
    fn voice(&self) {
        println!("ワン！");
    }
}

fn f<T: Creature>(crt: &T) {
    crt.voice();
}


fn main() {
    let human: Human = Human{};
    let dog: Dog = Dog{};

    f(&human);
    f(&dog);
}
