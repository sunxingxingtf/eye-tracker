// OpenCV offline
#include "flycapture/FlyCapture2.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <highgui.h>
#include <time.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>

using namespace FlyCapture2;
using namespace cv;
using namespace std;

// tcpclient:
// A class that creates a socket to allow communication between machines
// This allows streaming data to another machine
class tcpclient{
private:
	int status;
	struct addrinfo host_info;
	struct addrinfo *host_info_list;
	int socketfd;
	const char *msg;	
	int len;
	ssize_t bytes_sent;
	ssize_t bytes_recieved;
	char incoming_data_buffer[100];


public:
	void initialize(const char* hostname, const char* port){
		// need to block out memory and set to 0s
		memset(&host_info, 0, sizeof host_info);
		std::cout << "Setting up structs..." << std::endl;
		host_info.ai_family = AF_UNSPEC;
		host_info.ai_socktype = SOCK_STREAM;
		status = getaddrinfo(hostname, port, &host_info, &host_info_list);
		if (status != 0) std::cout << "getaddrinfo error" << gai_strerror(status);
		
		std::cout << "Creating a socket... " << std::endl;
		socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
		if (socketfd == -1) std::cout << "Socket error";

		std::cout << "Connecting..." << std::endl;
		status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
		if (status == -1) std::cout << "Connect error";
	}

	void sendMessage(const char *message){
		msg = message;
		len = strlen(msg);
		bytes_sent = send(socketfd, msg, len, 0);
	}

	char* recieveMessage(){
		bytes_recieved = recv(socketfd, incoming_data_buffer, 1000, 0);
		if (bytes_recieved == 0) std::cout << "Host shut down." << std::endl;
		if (bytes_recieved == -1) std::cout << "Recieve error!" << std::endl;
		return incoming_data_buffer;
	}

	void disconnect(){
		std::cout << "Closing socket..." << std::endl;
		freeaddrinfo(host_info_list);
		shutdown(socketfd,2);
	}

	
};

// CStopWatch:
// A simple timer class with Start, Stop, and GetDuration function calls 
class CStopWatch{
private:
	clock_t start;
	clock_t finish;

public:
	double GetDuration() {return (double)(finish-start) / CLOCKS_PER_SEC;}
	void Start() {start = clock();}
	void Stop() {finish = clock();}

};


// Initialize global variables: These are necessary for GUI function
int max_solves_slider_max = 100;
int max_solves_slider;
int max_solves = 100;

Vec<int,4> coordinates;
float tracking_params[] = {0, 0, 0, 0};

int min_dist_slider_max = 100;
int min_dist_slider;
int min_dist;

int canny_threshold_slider_max = 255;
int canny_threshold_slider;
int canny_threshold;

int center_threshold_slider_max = 255;
int center_threshold_slider;
int center_threshold;

int min_radius_slider_max = 99;
int min_radius_slider;
int min_radius;

int max_radius_slider_max = 100;
int max_radius_slider;
int max_radius;

int med_blur_slider_max = 255;
int med_blur_slider;
int med_blur;

int bin_threshold_slider_max = 255;
int bin_threshold_slider;
int bin_threshold;

int rec_slider_max = 1;
int rec_slider;
int record_video;

int video_display_slider_max = 1;
int video_display_slider;
int video_display;

int run_program_slider_max = 1;
int run_program_slider = 1;
int run_program = 1;

int save_csv_slider_max = 1;
int save_csv_slider = 0;
int save_csv = 0;

int stream_data_slider_max = 1;
int stream_data_slider = 0;
int stream_data = 0;

bool isDrawing = false;
Point start, end;


// currentDateTime:
// Returns the current date and time
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d-%H%M%S", &tstruct);

    return buf;
}


// drawBox:
// A simple drawing function that draws a box around the ROI during setup
void drawBox(Point start, Point end, Mat& img){
	imshow("set",img);
	Scalar color = (255,0,0);
	rectangle(img, start, end, color, 10, 8, 0);
	return;
}


// mouseEvent:
// Records coordinates for where box is drawn. Saves coordinates for ROI
void mouseEvent(int evt, int x, int y, int flags, void* param){
	if(isDrawing){
		if(evt==CV_EVENT_LBUTTONUP){
	    		printf("up %d %d\n",x,y);
	        	isDrawing = false;
		        end.x = x;
		        end.y = y;
		        cv::Mat* image  = static_cast<cv::Mat *>(param);
			drawBox(start, end, *image);
			coordinates[2] = end.x-start.x;
			coordinates[3] = end.y-start.y;
	        	return;
    		}
	}
	else{
		if(evt==CV_EVENT_LBUTTONDOWN){
	        	printf("down %d %d\n",x,y);
		        isDrawing = true;
			start.x = x;
		        start.y = y;
			coordinates[0] = start.x;
			coordinates[1] = start.y;
        		return;
    		}
	}
}



// Initialize Trackbars
void min_dist_trackbar(int, void*){
	if (min_dist_slider==0){
		min_dist_slider=1;
	}
	min_dist = (int) min_dist_slider;
}

void canny_threshold_trackbar(int, void*){
	if (canny_threshold_slider==0){
		canny_threshold_slider=1;
	}
	canny_threshold = (int) canny_threshold_slider;
}

void center_threshold_trackbar(int, void*){
	if (center_threshold_slider==0){
		center_threshold_slider=1;
	}
	center_threshold = (int) center_threshold_slider;
}

void min_radius_trackbar(int, void*){
	if (min_radius_slider==0){
		min_radius_slider=1;
	}
	min_radius = (int) min_radius_slider;
}

void max_radius_trackbar(int,void*){
	max_radius = (int) max_radius_slider;
	min_radius_slider_max = max_radius-1;
}

void med_blur_trackbar(int,void*){
	if (med_blur_slider % 2 == 0){ // blur requires even input
		med_blur_slider=med_blur_slider+1;
	}
	if (med_blur_slider < 1){
		med_blur_slider=1;
	}
	med_blur = (int) med_blur_slider;
}

void bin_threshold_trackbar(int,void*){
	bin_threshold = (int) bin_threshold_slider;
}

void run_program_trackbar(int,void*){
	run_program = (int) run_program_slider;
}

void rec_trackbar(int,void*){
	record_video = (int) rec_slider;
}

void video_display_trackbar(int,void*){
	video_display = (int) video_display_slider;
}

void save_csv_trackbar(int,void*){
	save_csv = (int) save_csv_slider;
}

void stream_data_trackbar(int,void*){
	stream_data = (int) stream_data_slider;
}

// Main function:
// This program will track the eye
int main(){
	// Setup tcpclient
	tcpclient client;
	std::string server = "y4.cns.nyu.edu";
	std::string port = "5555";
	client.initialize(server.c_str(),port.c_str());

	// initialize timer rec
	double delay;
	CStopWatch sw;
	
	// save file
	cout << "\nChoose a file name to save to. Defaults to current date and time...\n";
	string input = "";
	string filename;
	string video_filename;
	getline(cin, input);
	if (input == ""){
		filename = currentDateTime();
		video_filename = currentDateTime();
	}
	else{
		filename = input;
		video_filename = input;
	}

	filename.append(".csv");
	const char *fn = filename.c_str();
	
	ofstream save_file (fn);

	// Initialize camera for setup
	Error error;
	Camera camera;
	CameraInfo camInfo;

	// Connect to the camera
	error = camera.Connect(0);
	if(error != PGRERROR_OK){
		std::cout << "failed to connect to camera..." << std::endl;
		return false;
	}

	error = camera.GetCameraInfo(&camInfo);
	if (error != PGRERROR_OK){
		std::cout << "failed to get camera info from camera" << std::endl;
		return false;
	}

	std::cout << camInfo.vendorName << " "
			<< camInfo.modelName << " "
			<< camInfo.serialNumber << std::endl;
	
		error = camera.StartCapture();
	if(error==PGRERROR_ISOCH_BANDWIDTH_EXCEEDED){
		std::cout << "bandwidth exceeded" << std::endl;
		return false;
	}
	else if (error != PGRERROR_OK){
		std::cout << "failed to start image capture" << std::endl;
		return false;
	}
	



	// Setup: User draws rectangle around ROI
	//  Wait for 'c' to be pushed to move on
	// If user enters 'c' without drawing an ROI, use full image
	cout << "click and drag on image to select reference size\n";
	cout << "press c to continue\n";
	char kb = 0;	
	namedWindow("set",WINDOW_NORMAL);
	
	
	Image tmpImage;
	Image rgbTmp;
	cv::Mat tmp;
	while(kb != 'c'){
		// Grab frame from buffer
		Error error = camera.RetrieveBuffer(&tmpImage);
		if (error != PGRERROR_OK){
			std::cout<< "capture error" << std::endl;
			return false;
		}
		
		// Convert image to OpenCV color scheme
		tmpImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbTmp);

		unsigned int rowBytes = (double)rgbTmp.GetReceivedDataSize()/(double)rgbTmp.GetRows();

		tmp = cv::Mat(rgbTmp.GetRows(),rgbTmp.GetCols(),CV_8UC3,rgbTmp.GetData(),rowBytes);
	
		imshow("set",tmp);
	
	        cvSetMouseCallback("set", mouseEvent, &tmp);
		if (coordinates[3] != '\0'){
			drawBox(start, end, tmp);
			imshow("set",tmp);
		}
		kb = cvWaitKey(30);
	}
	// Set ROI to image size if no coordinates specified
	if (coordinates[0] == 0 and coordinates[1] == 0){
		coordinates[0] = 0;
		coordinates[1] = 0;
		coordinates[2] = tmp.cols;
		coordinates[3] = tmp.rows;
	}
	// Make sure coordinates array is in proper form:
	// elements 0 and 1 should be less than elements 2 and 3 respectively
	else{
		if (coordinates[0] > coordinates[2]){
			int hold = coordinates[0];
			coordinates[0] = coordinates[2]+coordinates[0];
			coordinates[2] = hold+coordinates[0];
		}
		if (coordinates[1] > coordinates[3]){
			int hold = coordinates[1];
			coordinates[1] = coordinates[3]+coordinates[1];
			coordinates[3] = hold+coordinates[1];
		}
	}
	destroyWindow("set");


	// Initialize variables for sliders
	
	int dp = 1;
	
	// Min Dist
	min_dist = 1;
	min_dist_slider = 1;
	
	// Canny threshold
	canny_threshold = 10;
	canny_threshold_slider = 10;
	
	// Center threshold
	center_threshold = 10;
	center_threshold_slider = 10;
	
	// Max radius
	max_radius = 140;
	max_radius_slider = 100;
	max_radius_slider_max = min(coordinates[2]-coordinates[0],coordinates[3]-coordinates[1])+100;

	// Min radius
	min_radius = 50;
	min_radius_slider = 50;
	min_radius_slider_max = max_radius_slider_max-1;

	// Binary threshold
	bin_threshold = 21;
	bin_threshold_slider = 21;

	// Blur
	med_blur = 75;
	med_blur_slider_max = min(coordinates[2]-coordinates[0],coordinates[3]-coordinates[1])-10;
	med_blur_slider = 75;

	// Video display
	video_display_slider_max = 1;
	video_display_slider = 1;
	video_display = 1;

	// Record video
	record_video = 0;
	rec_slider = 0;
	rec_slider_max = 1;
	
	// Set up window with ROI and offset
	Mat window;
	Rect myROI(coordinates[0],coordinates[1],coordinates[2],coordinates[3]);
	Vec<float,2> offset;
	offset[0] = coordinates[0];
	offset[1] = coordinates[1];
	
	// setup windows
	namedWindow("window",WINDOW_NORMAL);
	namedWindow("filtered",WINDOW_NORMAL);
	cvNamedWindow("control",WINDOW_NORMAL);
	resizeWindow("window",400,300);
	resizeWindow("filtered",250,200);
	resizeWindow("control",250,80);
	moveWindow("window",0,0);
	moveWindow("filtered",400,0);
	moveWindow("control",650,0);
	bool refresh = true;

	// Initialize video recorder
	VideoWriter vid;
	double fps = 20;
	Size S = Size((int) rgbTmp.GetCols(), (int) rgbTmp.GetRows());
	video_filename = video_filename.append("-video.avi"); 
	vid.open(video_filename,1196444237,fps,S,true);



	// make sliders
	createTrackbar("Min Distance", "control", &min_dist_slider,min_dist_slider_max,min_dist_trackbar);
	createTrackbar("Canny Threshold", "control", &canny_threshold_slider, canny_threshold_slider_max, canny_threshold_trackbar);
	createTrackbar("Center Threshold", "control", &center_threshold_slider,center_threshold_slider_max, center_threshold_trackbar);
	createTrackbar("Min Radius", "control", &min_radius_slider,min_radius_slider_max, min_radius_trackbar);
	createTrackbar("Max Radius", "control", &max_radius_slider,max_radius_slider_max, max_radius_trackbar);
	createTrackbar("Median blur", "control", &med_blur_slider, med_blur_slider_max, med_blur_trackbar);
	createTrackbar("Bin Threshold", "control", &bin_threshold_slider, bin_threshold_slider_max, bin_threshold_trackbar);
	createTrackbar("Display Video","control",&video_display_slider, video_display_slider_max, video_display_trackbar);
	createTrackbar("Record","control",&rec_slider,rec_slider_max,rec_trackbar);
	createTrackbar("Stream Data","control",&stream_data_slider,stream_data_slider_max,stream_data_trackbar);
	
	sw.Start(); // start timer
	char key = 0;
	
	int reset = 1000;
	int iter = 0;

	// This is the main loop for the funcion
	while(key != 'q'){
		
		//start timer
		Image rawImage;
		Error error = camera.RetrieveBuffer( &rawImage );
		if (error != PGRERROR_OK ){
			std::cout << "capture error" << std::endl;
			continue;
		}
		
		Image rgbImage;
		rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
		// convert to OpenCV Mat
		unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize()/(double)rgbImage.GetRows();
		Mat image = Mat(rgbImage.GetRows(), rgbImage.GetCols(),CV_8UC3, rgbImage.GetData(),rowBytes);

		// convert to gray	
		Mat image_gray;
		image_gray = image(myROI);
		
		// Pre-process
		cvtColor( image_gray, image_gray, CV_BGR2GRAY);
		blur(image_gray,image_gray,Size(med_blur,med_blur));
		threshold(image_gray, image_gray, bin_threshold, 255, THRESH_BINARY);
		GaussianBlur( image_gray, image_gray, Size(9, 9), 2, 2);


		// Apply Hough Transform to find circles
		vector<Vec3f> circles;
		HoughCircles( image_gray, circles, CV_HOUGH_GRADIENT, dp, min_dist, canny_threshold, center_threshold, min_radius, max_radius);
		

		//Draw circles detected
		float x=0;
		float y=0;
		float r=0;
		float centerX;
		float centerY;
		
		if (circles.size()>0){
			for( size_t i=0; i< circles.size(); i++)
			{
				x=x+circles[i][0];
				y=y+circles[i][1];
				r=r+circles[i][2];
			}
		
			centerX=cvFloor(x/circles.size()+offset[0]);
			centerY=cvFloor(y/circles.size()+offset[1]);
		
			Point center(cvRound(centerX), cvRound(centerY));
			
			if (video_display==1){
				//int radius = cvRound(r/circles.size());
				int radius = (min_radius+max_radius)/2;
				// circle center
				circle(image,center,3,Scalar(0,255,0),-1,8,0);
				// circle outline
				circle(image,center,radius,Scalar(0,0,255),3,8,0);
			}
		}
		else{
			centerX = 0;
			centerY = 0;
		}	
		
		// Record the video - this is slow!!
		if (record_video == 1){
			vid.write(image);
			sw.Stop();
	                delay = sw.GetDuration();
		}
		

		if (video_display==1 or save_csv==1){
			if (video_display==1){
				imshow("window",image);
				imshow("filtered",image_gray);
			}
		}
		

		
		key = waitKey(1);
        	save_file << centerX << "," << centerY << "," << delay << endl;
		sw.Start(); // restart timer
		
		if (stream_data == 1){
			std::stringstream sstm;
			sstm << centerX << "," << centerY << endl;
			const std::string stmp = sstm.str();
			const char* msg = stmp.c_str();
			client.sendMessage(msg);
		}

	}
	
	std::stringstream quit;
	quit << 'q';
	const std::string qt = quit.str();
	const char* q = qt.c_str();
	client.sendMessage(q);

}
