
use std::io;

struct Project {
    name: String,
    children: Vec<Project>,
}

impl Project {
    fn new(in_name: String) -> Project {
        let ch: Vec<Project> = Vec::new();

        Project{ name: in_name, children: ch }
    }

    fn from(in_name: &str) -> Project {
        let ch: Vec<Project> = Vec::new();

        Project{ name: String::from(in_name), children: ch }
    }
}

fn main() {
    println!("Please input the projects");
    let projects_str = String::from("a,b,c,d,e,f");
    // let mut projects_str = String::new();
    //io::stdin().read_line(&mut projects_str).expect("Failed to read in projects");

    println!("Please input the dependencies");
    let mut dependencies_str = String::from("(a;d),(f;b),(b;d),(f;a),(d;c)");
    // let mut dependencies_str = String::new();
    //io::stdin().read_line(&mut dependencies_str).expect("Failed to read in dependencies");

    let projects_vec = projects_str.trim().split(",").map(|p| Project::from(p)).collect::<Vec<Project>>();
    dependencies_str = dependencies_str.replace("(", "");
    dependencies_str = dependencies_str.replace(")", "");
    let dependencies_vec = dependencies_str.trim().split(",").collect::<Vec<&str>>();

    println!("Projects");
    for p in projects_vec {
        println!("{}", p.name);
    }
    println!("Dependencies: {:?}", dependencies_vec);
}
