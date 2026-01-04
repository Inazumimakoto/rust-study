fn main() {
    let s1 = String::from("hello");
    let s2 = String::from("world");

    let result = longest(&s1,&s2);
    println!("{}",result);
}

fn longest(x: &str,y: &str) -> &str {
    if x.len() > y.len() {x} else {y}
}
