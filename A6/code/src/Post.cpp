#include "Post.hpp"

Post::Post(string title, string message, int id, string image_address, string author, PostType post_type, string extra, int course_id) : author(author), id(id), course_id(course_id), extra(extra), image_address(image_address), post_type(post_type), message(message), title(title) {
    available = true;
}