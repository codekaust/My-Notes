// RUN: node app.js

// // BASIC ASYNC
// //////////////////// 1 ////////////////////
// console.log("Here")

// // click listeners also work similarly by keeping them in web apis (see SS)
// setTimeout(() => {
//     console.log("in timeout")
// }, 3000)

// // callbacks not necessarily async
// const items = [1,2,3]
// items.forEach(item => {
//     console.log(item)
// })

// console.log("there")
// ///////////////////////////////////////////



// // CALLBACKS
// //////////////////// 2 ////////////////////
// console.log('START')

// //////////// 2.1 ////////////
// // // dummy func 
// // function loginUser(email, password){
// //     // we say that login will take 1500 milliseconds (random)
// //     setTimeout(()=> {
// //         console.log("now we got data")
// //         let data_we_got = {
// //             userEmail: email, 
// //             userName: 'random_username'
// //         }
// //         return data_we_got;
// //     }, 1500);
// // }

// // // call function which gets user
// // const user = loginUser("me@gmail.com", "123_as_pass")

// // // lets log user
// // console.log(user) // prints undefined, why? Cause the request is not fulfilled yet. The program though will end for data to come and will finish only afterwards
// // // so synchronous code did not work for us
// /////////////////////////////

// //////////// 2.2 ////////////
// // dummy func 2
// function loginUser2(email, password, callback){
//     // we say that login will take 1500 milliseconds (random)
//     setTimeout(()=> {
//         console.log("now we got data")
//         let data_we_got = {
//             userEmail: email, 
//             userName: 'random_username'
//         }
//         callback(data_we_got);
//     }, 1500);
// }

// function getSomeUserVideo(email, callback){
//     // we say that login will take 1500 milliseconds (random)
//     setTimeout(()=> {
//         let videos = ['video_f1', 'video_f2']
//         callback(videos);
//     }, 1000);
// }

// const user2 = loginUser2("me@gmail.com", "123_as_pass", user=>{
//     console.log("Printing user in callback function: ", user)
//     getSomeUserVideo(user.email, videos=>{
//         console.log('printing video in user callback -> video callback: ', videos)
//     })
// })
// /////////////////////////////

// console.log('END.', 'Did this print at end?')

// // NOTE: This becomes super complex as the nesting and the number of callbacks required increase
// ///////////////////////////////////////////



// // PROMISES
// //////////////////// 3 ////////////////////
// console.log('START')

// //////////// 3.1 ////////////
// const promise = new Promise(
//     // This is executor. resolve and reject are like return in promise.then, catch scenario
//     (resolve, reject) => {
//         setTimeout(()=>{
//             let data_onsuccess = {
//                 'data':1
//             }

//             let success = true
            
//             if (success){
//                 console.log("got data in promise")
//                 resolve(data_onsuccess)
//             }else{
//                 reject(new Error("got error"))
//             }
//     }, 
    
//     2000)
// })

// // consume promise
// promise
//     // You can have promise.then(...).then(...) if ur promise was returning another promise
//     // NOTE: also check out Promise.all for executing multiple promises together
//     .then(data => {
//         console.log("promise.then printing data", data)
//     })
//     .catch(error => {
//         console.log(error.message)
//     });
// /////////////////////////////

// console.log('END.', 'Did this print at end?')
// ///////////////////////////////////////////

// ASYNC AWAIT: Makes it look like synchronous code
//////////////////// 4 ////////////////////
console.log('START')

function loginUser(email, password){
    return new Promise(
        (resolve, reject) => {
            setTimeout(()=>{
                let data_onsuccess = {
                    'data':1
                }
    
                let success = true
                
                if (success){
                    console.log("got data in promise")
                    resolve(data_onsuccess)
                }else{
                    reject(new Error("got error"))
                }
        }, 
        
        2000)
    })
}

async function displayUser(){
    const user = await loginUser("email", "password");
    console.log(user)
}

displayUser()

// NOTE: Error handling here will be in try catch

console.log('END.', 'Did this print at end?')
///////////////////////////////////////////
