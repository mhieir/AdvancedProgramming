#include "Cloud.hpp"
#include "Primary.hpp"

Cloud::Cloud() {
    post_number = 1;
}

int Cloud::findCourseByPost(int index) {
    for(int i = 0; i < (int) posts.size(); i++) {
        if(posts[i]->getId() == index) {
            return posts[i]->getCourseId();
        }
    }
}

void Cloud::addPost(string title, string message, string image_address, string author, PostType post_type, string extra, int course_id) {
    posts.push_back(new Post(title, message, post_number, image_address, author, post_type, extra, course_id));
    post_number++;
}

void Cloud::removePost(int post_id) {
    for(int i = 0; i < (int) posts.size(); i++) {
        if(posts[i]->getId() == post_id) {
            posts.erase(posts.begin() + i);
            return;
        }
    }
}

bool Cloud::isInPost(int post_id) {
    for(int i = 0; i < (int) posts.size(); i++) {
        if(posts[i]->getId() == post_id) {
            return true;
        }
    }
    return false;
}

bool Cloud::isTAForm(int post_id) {
    for(int i = 0; i < (int) posts.size(); i++) {
        if(posts[i]->getId() == post_id and posts[i]->getPostType() == _TA_FORM) {
            return true;
        }
    }
    return false;
}

void Cloud::showOnePost(vector<string>& output, int post_id) {
    for(int i = 0; i < (int) posts.size(); i++) {
        if(posts[i]->getId() == post_id) {
            if(posts[i]->getPostType() == _NORMAL) {
                output.push_back(to_string(posts[i]->getId()) + SPACE + posts[i]->getTitle() + SPACE +  posts[i]->getMessage());
            }
            else {
                output.push_back(to_string(posts[i]->getId()) + SPACE + posts[i]->getTitle() + END_LINE + posts[i]->getExtra() + END_LINE + posts[i]->getMessage());
            }
        }
    }
    output.push_back(END_LINE);
}

void Cloud::showOnePostCourseChannel(vector<string>& output, int post_id) {
    for(int i = 0; i < (int) posts.size(); i++) {
        if(posts[i]->getId() == post_id) {
            output.push_back(to_string(posts[i]->getId()) + SPACE + posts[i]->getAuthor() + SPACE + posts[i]->getTitle() + SPACE + posts[i]->getMessage());
        }
    }
    output.push_back(END_LINE);
}

void Cloud::showPosts(vector<string>& output) {
    for(int i = (int) posts.size() - 1; 0 <= i; i--) {
        // output.push_back(to_string(posts[i]->getId())+ SPACE + posts[i]->getTitle() + END_LINE);
        output.push_back(to_string(posts[i]->getId()));
        output.push_back(posts[i]->getTitle());
    }
}

void Cloud::showPostsCourseChannel(vector<string>& output) {
    for(int i = (int) posts.size() - 1; 0 <= i; i--) {
        output.push_back(to_string(posts[i]->getId()) + SPACE + posts[i]->getAuthor() + SPACE + posts[i]->getTitle() + END_LINE);
    }
}