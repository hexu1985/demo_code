struct User {
    1: string uid,  
    2: string uname,  
    3: bool usex,  
    4: i16 uage,  
    5: optional string details,
}

struct UserQuery {
    1: string uid,
    2: optional string details,
}

service UserService {
    void add(1: User u),  
    User get(1: UserQuery qry),  
    void add_v2(1: User u), 
} 

