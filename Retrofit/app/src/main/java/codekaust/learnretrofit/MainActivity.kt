package codekaust.learnretrofit

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val retrofit: Retrofit = Retrofit.Builder()
            .baseUrl("https://jsonplaceholder.typicode.com/")
            .addConverterFactory(GsonConverterFactory.create())
            .build()

        val jsonPlaceHolderAPI = retrofit.create(JSONPlaceHolderAPI::class.java)

        /************GET*********/

        val call: Call<List<Post>> = jsonPlaceHolderAPI.getPosts()

//        call.execute()

        call.enqueue(object : Callback<List<Post>> {
            override fun onFailure(call: Call<List<Post>>, t: Throwable) {
                text_view.text = t.message
            }

            override fun onResponse(call: Call<List<Post>>, response: Response<List<Post>>) {
                if (response.isSuccessful) {
                    val posts: List<Post>? = response.body()

                    if (posts != null) {
                        for (post in posts) {
                            var content = ""
                            content += "ID: " + post.id + "\n"
                            content += "User ID: " + post.userId + "\n"
                            content += "Title: " + post.title + "\n"
                            content += "Text: " + post.text + "\n\n"

                            text_view.append(content)
                        }
                    }
                } else {
                    text_view.text = response.code().toString()
                }
            }

        })

        /**********GET_END********/

        /**********POST***********/
        //we wont put in id as this is added by REST api for every post
        val post: Post = Post(5, null, "TitleString", "BodyString")

        val call2: Call<Post> = jsonPlaceHolderAPI.createPost(post)

        call2.enqueue(object : Callback<Post> {
            override fun onFailure(call: Call<Post>, t: Throwable) {

            }

            override fun onResponse(call: Call<Post>, response: Response<Post>) {
                if (!response.isSuccessful) {
                    Toast.makeText(this@MainActivity, "Code: " + response.code(), Toast.LENGTH_SHORT)
                        .show()
                    return
                }

                val postResponse: Post? = response.body()

                var content = ""

                if (postResponse != null) {
                    content += "Code: " + response.code()
                    content += "ID: " + postResponse.id + "\n"
                    content += "User ID: " + postResponse.userId + "\n"
                    content += "Title: " + postResponse.title + "\n"
                    content += "Text: " + postResponse.text
                }

                Toast.makeText(this@MainActivity, content, Toast.LENGTH_SHORT).show()
            }

        })

        /**********POST_END***********/
    }
}