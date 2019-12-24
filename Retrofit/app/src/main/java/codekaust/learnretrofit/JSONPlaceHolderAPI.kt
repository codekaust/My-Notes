package codekaust.learnretrofit

import retrofit2.Call
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.Url
import retrofit2.http.QueryMap



interface JSONPlaceHolderAPI{

    @GET("posts")
    fun getPosts() : Call<List<Post>>

    @POST("posts")
    fun createPost(@Body post: Post) : Call<Post>
}