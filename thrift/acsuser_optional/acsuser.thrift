struct User {
    1: string uid,  
    2: string uname,  
    3: bool usex,  
    4: i16 uage,  
    5: string opt1,
    6: optional string opt2,
}

service UserService {
    void add(1: User u),  
    User get(1: string uid),  
} 

