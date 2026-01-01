use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("Guess the number!");//数を当ててごらん
    
    let secret_number = rand::thread_rng().gen_range(1..101);

    println!("The secret number is: {}",secret_number);

    println!("Please input your guess.");//ほら，予想を入力してね

    let mut guess = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line"); //行の読み込みに失敗

    println!("You guessed: {}",guess);//次のように予想しました

    let guess: u32 = guess.trim().parse()
        .expect("Please type a number!");

    match guess.cmp(&secret_number) {
        Ordering::Less => println!("Too small!"),
        Ordering::Greater => println!("Too big!"),
        Ordering::Equal => println!("You win!"),
    }


}
