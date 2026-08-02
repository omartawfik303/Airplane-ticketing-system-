#include<iostream>
#include<fstream>
#include<cstring>
#include <iomanip>

#define X 20
#define Y 50
#define Z 100
#define row 6
#define column 10  

using namespace std;

struct userinfo // file structure for admin and admin info
{
	string userid;
	string password;
	string FName;
	string LName;
	string Age;
	string PhoneNum;
	string Security_ver;
};

struct FlightDetails
{
	string flightID;
	char deploc [50];
	char desloc [50];
	char date [20];
	int duration;
	char deptime [20];
	char arrtime [20];
};

struct Seating
{
	string flightID;
	char Seats [row][column];
};

struct Payment
{
	int id;
	string userid;
	string flightID;
	int numAdult;
	int numChild;
	int totnum;
	string paymethod;
	int price;
};

int main()
{
	int a, U=0, F=0, P=0;
	int fileread = 0;
	int mainexit, loginexit=0, bookingexit=0, paymentexit=0;
	int i=0, j=0, k=0, l=0;
	int exit1=0, exit2=0, exit3=0, exit4=0, exit5=0, exit6=0; 
	int numAdult=0, numChild=0, totnum=0, seatAva=0;
	int Operation1, Operation2, Operation3, Operation4;
	int selected;	
	char selRow;
	int selColumn;
	char confirm = 'N';
	string cc,accnum,cvv,otp;
	
	struct userinfo alluserinfo[X];
	struct userinfo newuser;
	struct userinfo user;
	struct FlightDetails AllFlightInfo[Y];
	struct FlightDetails FlightSearch;
	struct FlightDetails FlightUser;
	struct Seating SeatInfo[Y];
	struct Seating SeatUser[Y];
	struct Payment AllPaymentInfo[Z];
	struct Payment PaymentInfo;
		
	//User Read
	ifstream read;
	read.open("User Info.txt", ios::app);
	if(read.fail())
	{
		cout<<"File for User Details Not Found";
		fileread = 1;
	}		

	else
	{
		i=0;
		while(!read.eof())
		{
			read>>alluserinfo[i].userid;
			read>>alluserinfo[i].password;
			read>>alluserinfo[i].FName;
			read>>alluserinfo[i].LName;
			read>>alluserinfo[i].Age;
			read>>alluserinfo[i].PhoneNum;
			read>>alluserinfo[i].Security_ver;
			if (!alluserinfo[i].userid.empty())
				U++;
			i++;	
		}
		read.close();
	}
	
	//Flight Read
	ifstream flightsinput;
	flightsinput.open("Flights.txt", ios::app);
	if(flightsinput.fail())
	{
		cout<<"File for Flight Details Not Found";
		fileread = 1;
	}
	else
	{
		i=0;
		while (!flightsinput.eof())
		{
			flightsinput>>AllFlightInfo[i].flightID;
			flightsinput>>AllFlightInfo[i].deploc;
			flightsinput>>AllFlightInfo[i].desloc;
			flightsinput>>AllFlightInfo[i].date;
			flightsinput>>AllFlightInfo[i].duration;
			flightsinput>>AllFlightInfo[i].deptime;
			flightsinput>>AllFlightInfo[i].arrtime;
			if (!AllFlightInfo[i].flightID.empty())
	        	F++;
			i++;
		}
		flightsinput.close();
	}
	
	//Seating Read
	ifstream seatinginput;
	seatinginput.open("Seating.txt");
	if(seatinginput.fail())
	{
		cout<<"File for Seating Details Not Found";
		fileread = 1;
	}		
	else
	{
		for (i=0; i<F; i++)
		{
			seatinginput>>SeatInfo[i].flightID;
			for (j=0; j<row; j++)
			{
				for (k=0; k<column; k++)
				{
					seatinginput>>SeatInfo[i].Seats[j][k];
				}
			}
		}	
		seatinginput.close();
	}
	
	//Payment Read
	ifstream paymentinput;
	paymentinput.open("Payments.txt");
	if(paymentinput.fail())
	{
		cout<<"File for Payment Details Not Found";
		fileread = 1;
	}
	else
	{
		i=0;
		while (!paymentinput.eof())
		{
			paymentinput>>AllPaymentInfo[i].id;
			paymentinput>>AllPaymentInfo[i].userid;
			paymentinput>>AllPaymentInfo[i].flightID;			
			paymentinput>>AllPaymentInfo[i].numAdult;
			paymentinput>>AllPaymentInfo[i].numChild;
			paymentinput>>AllPaymentInfo[i].totnum;
			paymentinput>>AllPaymentInfo[i].paymethod;
			paymentinput>>AllPaymentInfo[i].price;
			i++;
		}
		paymentinput.close();
		
	}
	P = i;	
		
	// User Panel
	while(mainexit == 0 && fileread == 0)
	{
		
		cout<<"|___________________________________________________________|"<<endl;
		cout<<"|\t\tWelcome to the Main Panel                   |"<<endl;
		cout<<"|___________________________________________________________|"<<endl;
		cout<<"|1. Login                                                   |"<<endl;
		cout<<"|___________________________________________________________|"<<endl;
		cout<<"|2. Register New User                                       |"<<endl;
		cout<<"|___________________________________________________________|"<<endl;
		cout<<"|3. Forget Password                                         |"<<endl;
		cout<<"|___________________________________________________________|"<<endl;
		cout<<"|4. Exit                                                    |"<<endl;
		cout<<"|___________________________________________________________|"<<endl;
		cout<<"Choose your Operation: ";
		cin>>Operation1; 
		cout<<endl;		

		if (Operation1==1) // Login panel
		{
			Operation2=0;
			a=0;
			ifstream read;
			read.open("User Info.txt");
			for (i=0; i<U; i++)
			{
				read>>alluserinfo[i].userid;
				read>>alluserinfo[i].password;
				read>>alluserinfo[i].FName;
				read>>alluserinfo[i].LName;
				read>>alluserinfo[i].Age;
				read>>alluserinfo[i].PhoneNum;
				read>>alluserinfo[i].Security_ver;
			}
			read.close();			
			cout<<"|___________________________________________________________|"<<endl;
			cout<<"|\t\t         Login Panel \t\t\t    |"<<endl;	
			cout<<"|___________________________________________________________|"<<endl; 	
			cout<<"Enter User ID       : ";
  			cin>>user.userid; 
			cout<<"Enter User Password : ";
			//Check if user iput is the same as whats saved inside the txt file
  			cin>>user.password;
  				      
  			for (i=0; i<U; i++)
  			{
  				if(user.userid == alluserinfo[i].userid)
				{
				 	if(user.password == alluserinfo[i].password)
				 	{
				 		cout<<endl;
				 		cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
				 		cout<<"Login Successful"<<endl;
				 		cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
				 		a=1;
				 		loginexit=0;
				 		user = alluserinfo[i];
				 		sleep(1);
				 		system("cls");
				 		
				 		while (loginexit == 0)
				 		{
				 			loginexit=0;
				 			cout<<"|___________________________________________________________|"<<endl;
							cout<<"|\t\tWelcome To The Managing Panel               |"<<endl;	
							cout<<"|___________________________________________________________|"<<endl;
							cout<<"|1. Flight Booking                                          |"<<endl;
							cout<<"|___________________________________________________________|"<<endl;
							cout<<"|2. View User Info                                          |"<<endl;
							cout<<"|___________________________________________________________|"<<endl;
							cout<<"|3. View Past Bookings                                      |"<<endl;
							cout<<"|___________________________________________________________|"<<endl;
							cout<<"|4. Exit Managing Panel                                     |"<<endl;
							cout<<"|___________________________________________________________|"<<endl;
							cout<<"Choose your Operation: ";
							cin>>Operation2; 
							cout<<endl;
							
							if (Operation2 == 1) //Flight Booking
							{
								bookingexit=0;
								Operation3=0;
								cout<<endl;
								cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
								cout<<"Entering Flight Booking"<<endl;
								cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
								sleep(1);
								system("cls");
								cout<<"===================================================================================================================="<<endl;
								cout<<"Flight Booking"<<endl;
								cout<<"===================================================================================================================="<<endl<<endl;
							
								while(bookingexit == 0)
								{
									bookingexit=0;
									cout<<"*********************************************"<<endl;
									cout<<"*   Choose an Operation To Perform          *"<<endl;
									cout<<"*********************************************"<<endl;
									cout<<"*   Option 1 : Check for All Flights        *"<<endl;
									cout<<"*   Option 2 : Check for Specific Flights   *"<<endl;
									cout<<"*   Option 3 : Booking Flight               *"<<endl;
									cout<<"*   Option 4 : Exit Booking                 *"<<endl;
									cout<<"*********************************************"<<endl;
									cout<<endl<<"Operation : ";
									cin>>Operation3;
									cout<<endl;	
									
									if (Operation3 == 1) //Check All FLights
									{
										cout<<"===================================================================================================================="<<endl;
										cout<<"Flights"<<endl;
										cout<<"===================================================================================================================="<<endl;
										cout<<"Flight ID   "<<"Departure Location\t"<<"Destination Location\t"<<"Date\t   "<<"Duration (H)  "<<"Departure Time\t"<<"Arrival Time\t"<<endl;
										cout<<"===================================================================================================================="<<endl;
											
										for (i=0; i<F; i++)
										{
											cout<<AllFlightInfo[i].flightID<<setw(17)<<AllFlightInfo[i].deploc<<setw(20)<<AllFlightInfo[i].desloc<<"\t\t"<<AllFlightInfo[i].date<<"\t"<<AllFlightInfo[i].duration<<"\t  "<<AllFlightInfo[i].deptime<<"\t\t"<<AllFlightInfo[i].arrtime;
											cout<<endl<<endl;
										}
										cout<<"===================================================================================================================="<<endl<<endl;
									}
										
									else if(Operation3 == 2) //Check for Specific Flights
									{
										do
										{
											exit1=0;
											exit2=0;
											cout<<"Enter Departure Location : ";
											cin>>FlightSearch.deploc;
											cout<<"Enter Destination Location : ";
											cin>>FlightSearch.desloc;
											cout<<endl<<endl;
												
											for (i=0; i<F; i++)
											{
												if (strcmp(FlightSearch.deploc, AllFlightInfo[i].deploc) == 0 && strcmp(FlightSearch.desloc, AllFlightInfo[i].desloc) == 0 && exit1==0)
													{
														cout<<"===================================================================================================================="<<endl;
														cout<<"Filtered Flights"<<endl;
														cout<<"===================================================================================================================="<<endl;
														cout<<"Flight ID   "<<"Departure Location\t"<<"Destination Location\t"<<"Date\t   "<<"Duration (H)  "<<"Departure Time\t"<<"Arrival Time\t"<<endl;
														cout<<"===================================================================================================================="<<endl;
														exit1 = 1;
													}
												if (strcmp(FlightSearch.deploc, AllFlightInfo[i].deploc) == 0 && strcmp(FlightSearch.desloc, AllFlightInfo[i].desloc) == 0)
													{
														cout<<AllFlightInfo[i].flightID<<setw(17)<<AllFlightInfo[i].deploc<<setw(20)<<AllFlightInfo[i].desloc<<"\t\t"<<AllFlightInfo[i].date<<"\t"<<AllFlightInfo[i].duration<<"\t  "<<AllFlightInfo[i].deptime<<"\t\t"<<AllFlightInfo[i].arrtime;
														cout<<endl<<endl;
														exit2 = 1;
													}
											}
												
											if (exit1 == 0)
											{
												cout<<"===================================================================================================================="<<endl;			
												cout<<"No available flights"<<endl;
												cout<<"Please re-enter"<<endl;
												cout<<"===================================================================================================================="<<endl<<endl;
												exit2 = 1;
											}
											
										} while(exit2 == 0);
										cout<<endl;						
									}
										
									else if (Operation3 == 3) //Booking Flight
									{
										exit3 = 0;
										exit4 = 0;
										exit5 = 0;
										totnum = 0;
										seatAva = 0;
										cout<<"Please enter the flight ID that you wish to book"<<endl;
										cin>>FlightUser.flightID;
											
										seatinginput.open("Seating.txt");				
										for (i=0; i<F; i++)
										{
											seatinginput>>SeatInfo[i].flightID;
											for (j=0; j<row; j++)
											{
												for (k=0; k<column; k++)
												{
													seatinginput>>SeatInfo[i].Seats[j][k];
												}
											}
										}	
										seatinginput.close();
								
										for (i=0; i<F; i++)
										{
												
											if (FlightUser.flightID == AllFlightInfo[i].flightID && exit4 == 0 && exit5 == 0)
											{
												selected = i;
												cout<<"Please Enter Number of Passengers"<<endl;
												cout<<"Adults : ";
												cin>>PaymentInfo.numAdult;
												cout<<"Children : ";
												cin>>PaymentInfo.numChild;
												PaymentInfo.totnum = PaymentInfo.numChild + PaymentInfo.numAdult;								
												cout<<"Total Number of Passengers : "<<PaymentInfo.totnum<<endl<<endl;						
													
												cout<<"===================================================================================================================="<<endl;
												cout<<"Selected Flight"<<endl;
												cout<<"===================================================================================================================="<<endl;
												cout<<"Flight ID   "<<"Departure Location\t"<<"Destination Location\t"<<"Date\t   "<<"Duration (H)  "<<"Departure Time\t"<<"Arrival Time\t"<<endl;
												cout<<"===================================================================================================================="<<endl;
												cout<<AllFlightInfo[i].flightID<<setw(17)<<AllFlightInfo[i].deploc<<setw(20)<<AllFlightInfo[i].desloc<<"\t\t"<<AllFlightInfo[i].date<<"\t"<<AllFlightInfo[i].duration<<"\t  "<<AllFlightInfo[i].deptime<<"\t\t"<<AllFlightInfo[i].arrtime;
												cout<<endl;
												cout<<"===================================================================================================================="<<endl;
												cout<<endl<<endl;
																
												FlightUser = AllFlightInfo[selected];
							
												cout<<"==========================================="<<endl;
												cout<<"   1  2  3  4  5  6  7  8  9  10"<<endl;
												cout<<"A  ";
												j = 0;
												for (k=0; k<column; k++)
												{											
													cout<<SeatInfo[selected].Seats[j][k]<<"  ";
													if (SeatInfo[selected].Seats[j][k] == '0')
														seatAva ++;
												}
												cout<<endl;
																		
												cout<<"B  ";
												j = 1;
												for (k=0; k<column; k++)
												{											
													cout<<SeatInfo[selected].Seats[j][k]<<"  ";
													if (SeatInfo[selected].Seats[j][k] == '0')
														seatAva ++;
												}
												cout<<endl;
														
												cout<<"C  ";
												j = 2;
												for (k=0; k<column; k++)
												{											
													cout<<SeatInfo[selected].Seats[j][k]<<"  ";
													if (SeatInfo[selected].Seats[j][k] == '0')
														seatAva ++;
												}
												cout<<endl;
																		
												cout<<"D  ";
												j = 3;
												for (k=0; k<column; k++)
												{										
													cout<<SeatInfo[selected].Seats[j][k]<<"  ";
													if (SeatInfo[selected].Seats[j][k] == '0')
														seatAva ++;
												}
												cout<<endl;
																
												cout<<"E  ";
												j = 4;
												for (k=0; k<column; k++)
												{											
													cout<<SeatInfo[selected].Seats[j][k]<<"  ";
													if (SeatInfo[selected].Seats[j][k] == '0')
														seatAva ++;
												}
												cout<<endl;
																		
												cout<<"F  ";
												j = 5;
												for (k=0; k<column; k++)
												{											
													cout<<SeatInfo[selected].Seats[j][k]<<"  ";
													if (SeatInfo[selected].Seats[j][k] == '0')
														seatAva ++;
												}
												cout<<endl;
													
												cout<<"==========================================="<<endl<<endl;
												cout<<"Number of Seats Available : "<<seatAva<<endl;
												cout<<"x : Not Available"<<endl;
												cout<<"0 : Available"<<endl<<endl;
												if (PaymentInfo.totnum > seatAva)
												{
													cout<<"Number of Passengers exceeded Number of Available Seats"<<endl;
													cout<<"Please Re-Enter"<<endl<<endl;
													exit4=1;
												}
												
												if (PaymentInfo.totnum < 1)
												{
													cout<<"Invalid Number of Passengers"<<endl;
													cout<<"Please Re-Enter"<<endl<<endl;
													exit4=1;
												}
												
													
												if (PaymentInfo.totnum <= seatAva)
												{			
													while (exit4 == 0 && exit5 == 0)
													{
														cout<<"xxxxxxxxxxxxxxxxxxxxx"<<endl;
														for (i=0; i<PaymentInfo.totnum; i++)					
														{	
															if (exit4 ==0)	
															{										
																cout<<"Seat #"<<i+1<<endl;
																cout<<"Select Seat Row"<<endl;
																cin>>selRow;
																if (selRow == 'A' || selRow == 'a')
																	j=0;
																else if (selRow == 'B'|| selRow == 'b')
																	j=1;
																else if (selRow == 'C'|| selRow == 'c')
																	j=2;
																else if (selRow == 'D'|| selRow == 'd')
																	j=3;
																else if (selRow == 'E'|| selRow == 'e')
																	j=4;
																else if (selRow == 'F'|| selRow == 'f')
																	j=5;
																else
																{
																	cout<<endl<<"Please Enter Valid Seat"<<endl;
																	exit4 = 1;
																}
																							
																cout<<"Select Seat Column"<<endl;
																cin>>selColumn;
																k = selColumn - 1;
																if (k < 0 || k > column)
																{
																	cout<<endl<<"Please Enter Valid Seat"<<endl;
																	exit4 = 1;
																}																					
																				
																if (SeatInfo[selected].Seats[j][k] == 'x')
																{
																	cout<<endl<<"Please Reselect Avalaible Seat"<<endl<<endl;
																	exit4 = 1;
																}
																	
																else if (SeatInfo[selected].Seats[j][k] == '@')
																{
																	cout<<"Please Do Not Select Selected Seat"<<endl<<endl;
																	exit4 = 1;
																}
																	
																else
																{
																	SeatInfo[selected].Seats[j][k] = '@';
																}
																	
																if (i == PaymentInfo.totnum-1)
																	exit5 = 1;
															}
														}
														cout<<"==========================================="<<endl;
														cout<<endl<<endl;
													}			
													
													if (exit4 == 0)
													{
														cout<<"===================================================================================================================="<<endl;
														cout<<"Booking Confirmation"<<endl;
														cout<<"===================================================================================================================="<<endl;
														cout<<"Seating For Flight "<<FlightUser.flightID<<endl;
														cout<<"Leaving From "<<FlightUser.deploc<<" and Arriving At "<<FlightUser.desloc<<endl;
														cout<<"Departure Time - "<<FlightUser.deptime<<" and Arrival Time - "<<FlightUser.arrtime<<endl;								
														cout<<"===================================================================================================================="<<endl;
														cout<<"   1  2  3  4  5  6  7  8  9  10"<<endl;
														cout<<"A  ";
														j = 0;
														for (k=0; k<column; k++)
														{											
															cout<<SeatInfo[selected].Seats[j][k]<<"  ";
														}
														cout<<endl;
																				
														cout<<"B  ";
														j = 1;
														for (k=0; k<column; k++)
														{											
															cout<<SeatInfo[selected].Seats[j][k]<<"  ";						
														}
															cout<<endl;
																
														cout<<"C  ";
														j = 2;
														for (k=0; k<column; k++)
														{											
															cout<<SeatInfo[selected].Seats[j][k]<<"  ";
														}
														cout<<endl;
																			
														cout<<"D  ";
														j = 3;
														for (k=0; k<column; k++)
														{										
															cout<<SeatInfo[selected].Seats[j][k]<<"  ";
														}
														cout<<endl;
																		
														cout<<"E  ";
														j = 4;
														for (k=0; k<column; k++)
														{											
															cout<<SeatInfo[selected].Seats[j][k]<<"  ";
														}
														cout<<endl;
																				
														cout<<"F  ";
														j = 5;
														for (k=0; k<column; k++)
														{											
															cout<<SeatInfo[selected].Seats[j][k]<<"  ";
														}
														cout<<endl<<"==========================================="<<endl<<endl;
															
														cout<<"Do You Wish To Book For This Flight? (Y/N) : ";
														cin>>confirm;
														cout<<endl;
														if (confirm == 'Y' || confirm == 'y')
														{	
															PaymentInfo.id = 
															paymentexit=0;
															while (paymentexit == 0)
															{																													
																cout << "===============PAYMENT DETAILS===============" << endl;
																cout<<"Booking for "<<PaymentInfo.totnum<<" Passengers"<<endl<<endl;

															    PaymentInfo.price = (PaymentInfo.numAdult * 100 * FlightUser.duration) + (PaymentInfo.numChild * 80 * FlightUser.duration);
															    cout<<"Price Per Adult = 100 x Duration of Flight ("<<FlightUser.duration<<"Hour(s))"<<endl;
															    cout<<"Price Per Child = 80 x Duration of Flight ("<<FlightUser.duration<<"Hour(s))"<<endl;
															    cout<<"Number of Adult(s) : "<<PaymentInfo.numAdult<<endl;
															    cout<<"Number of Children : "<<PaymentInfo.numChild<<endl;
															    cout<<"Price of Flight = RM "<<PaymentInfo.price<<endl<<endl;
															    
															    //user select the payment method from menu
															    cout<<"===============PAYMENT OPTIONS===============\n";
															    cout<<"1. Credit/Debit Card\n";
															    cout<<"2. Online Banking\n";
															    cout<<"3. Exit\n";
															    cout<<"\nSelect your options: ";
															    cin>>Operation4;
																cout<<"__________________________"<<endl;
																
															    if(Operation4 == 1)
															    {
															    	cout<<"\nEnter Credit/Debit Card Number (16 digits): ";
															    	cin>>cc;
															    	cout<<"Enter CVV (3 digits): ";
																	cin>>cvv;
																	
																	cout<<"Your Payment is Successfully Processed."<<endl<<endl;
																	PaymentInfo.paymethod = "Credit/Debit_Card";
																	paymentexit=1;
																}
																
																else if (Operation4 == 2)
																{
																	cout << "Account Details\n";
																	cout<<"__________________________\n";
															   		cout<<"Enter Account Number: ";
															   		cin>>accnum;
															    	cout<<endl<<"-----------P";
															    	sleep(1);
																	cout<<"ro";
																	sleep(1);
																	cout<<"cess";
																	sleep(1);
																	cout<<"ing-----------"<<endl;
																	sleep(1);
															    	cout<<"OTP Sent to "<<user.PhoneNum<<endl;
															    	cout<< "Enter OTP: ";
																	cin>>otp;
																	cout<<endl;
																	
																	cout<<"Your Payment is Successfully Processed."<<endl<<endl;
																	PaymentInfo.paymethod = "Online_Banking";
																	paymentexit=1;
																}
																
																else if (Operation4 ==3)
																	paymentexit = 2;
																	
															   	else
																	cout<<"Invalid Operation. Please Select 1, 2, 3."<<endl<<endl;
															}
															
															if (paymentexit=1)
															{			
																//Write into file that the seats are booked											
																ofstream seatingoutput;
																seatingoutput.open("Seating.txt");
																for(i=0; i<F; i++)
																{
																	seatingoutput<<SeatInfo[i].flightID<<endl;
																		
																	for(j=0; j<row; j++)
																	{
																		for(k=0; k<column; k++)
																		{
																			if (SeatInfo[i].Seats[j][k] == '@')
																			{
																				SeatInfo[i].Seats[j][k] = 'x';
																			}
																				
																			seatingoutput<<SeatInfo[i].Seats[j][k]<<" ";
																			
																		}
																		seatingoutput<<endl;
																	}
																	seatingoutput<<endl;
																}
																seatingoutput.close();
																PaymentInfo.id = (AllPaymentInfo[P-2].id + 1);
																PaymentInfo.userid = user.userid;
																PaymentInfo.flightID = FlightUser.flightID;
																
																
																//Write into file as receipt
																ofstream paymentoutput;
																paymentoutput.open("Payments.txt", ios::app);
																paymentoutput<<PaymentInfo.id<<" ";
																paymentoutput<<PaymentInfo.userid<<" ";
																paymentoutput<<PaymentInfo.flightID<<" ";
																paymentoutput<<PaymentInfo.numAdult<<" ";
																paymentoutput<<PaymentInfo.numChild<<" ";
																paymentoutput<<PaymentInfo.totnum<<" ";																
																paymentoutput<<PaymentInfo.paymethod<<" ";
																paymentoutput<<PaymentInfo.price<<" ";
																paymentoutput<<endl;
																paymentoutput.close();
																cout<<"Booking Confirmed"<<endl<<endl;
																exit5=1;
																P+1;
															}
														}
														
														
														else if (confirm != 'Y' && confirm != 'y')
														{
															cout<<"===================================================================================================================="<<endl;
															cout<<"Returning to Option Tab"<<endl;
															cout<<"===================================================================================================================="<<endl<<endl;
															exit5=1;
														}
															
													}	
												}
														
											}	
												else
													exit3 = 1;	
										}
									
										if (exit3 == 1 && exit4 == 0 && exit5 == 0)
											cout<<endl<<"Please enter valid flight ID"<<endl<<endl;
										if (exit4 == 1)
										{
											cout<<"===================================================================================================================="<<endl;
											cout<<endl<<"Please Re-Select from Options Tab"<<endl<<endl;
											cout<<"===================================================================================================================="<<endl<<endl;
										}
											
											
									}
									
										
									else if (Operation3 == 4) //Exit Booking
									{
										cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
										cout<<"Exiting Booking Page"<<endl;
										cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
										bookingexit=1;
										sleep(1);
										system("cls");
										Operation2 = 0;
									}
							
										
									else
										cout<<"Please Enter From Only The Available Options"<<endl<<endl;
												
									
								} 
							}
							
							else if (Operation2 == 2) //User Info
							{
								cout<<"|___________________________________________________________|"<<endl;
								cout<<"|\t\tViewing User Info                           |"<<endl;
								cout<<"|___________________________________________________________|"<<endl;
								cout<<"User ID : "<<alluserinfo[i].userid<<endl;
								cout<<"User Name : "<<alluserinfo[i].FName<<" "<<alluserinfo[i].LName<<endl;
								cout<<"User Age : "<<alluserinfo[i].Age<<endl;
								cout<<"User Phone Number : "<<alluserinfo[i].PhoneNum<<endl;
								cout<<"User Security Verification : "<<alluserinfo[i].Security_ver<<endl;
								cout<<"|___________________________________________________________|"<<endl<<endl<<endl;
							}
							
							else if (Operation2 == 3) //User Past Booking
							{
								//Payment Read
								ifstream paymentinput;
								paymentinput.open("Payments.txt");								
								i=0;
								while (!paymentinput.eof())
								{
									paymentinput>>AllPaymentInfo[i].id;
									paymentinput>>AllPaymentInfo[i].userid;
									paymentinput>>AllPaymentInfo[i].flightID;			
									paymentinput>>AllPaymentInfo[i].numAdult;
									paymentinput>>AllPaymentInfo[i].numChild;
									paymentinput>>AllPaymentInfo[i].totnum;
									paymentinput>>AllPaymentInfo[i].paymethod;
									paymentinput>>AllPaymentInfo[i].price;
									i++;
								}
								paymentinput.close();
								
								exit6=0;
								for (i=0; i<P; i++)
								{
									if (user.userid == AllPaymentInfo[i].userid)
									{
										cout<<"|___________________________________________________________|"<<endl;
										cout<<"|\t\tViewing User Past Bookings                  |"<<endl;
										cout<<"|___________________________________________________________|"<<endl;
										for (i=0; i<P; i++)
										{
											if (user.userid == AllPaymentInfo[i].userid)
											{
												cout<<"Payment ID           : "<<AllPaymentInfo[i].id<<endl;										
												cout<<"User ID              : "<<AllPaymentInfo[i].userid<<endl;
												cout<<"Flight ID            : "<<AllPaymentInfo[i].flightID<<endl;
												cout<<"No. Adult(s)         : "<<AllPaymentInfo[i].numAdult<<endl;
												cout<<"No of Children       : "<<AllPaymentInfo[i].numChild<<endl;
												cout<<"Total No. Passengers : "<<AllPaymentInfo[i].totnum<<endl;	
												cout<<"Payment Method       : "<<AllPaymentInfo[i].paymethod<<endl;
												cout<<"Price                : "<<AllPaymentInfo[i].price<<endl;
												cout<<endl;
												exit6=1;																						
											}	
										}
										sleep(1);
									}	
																
								}
								if (exit6 == 0)
								{
									cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<endl;
									cout<<"\t\tUser Have Not Booked Any Flights            "<<endl;
									cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<endl;
									sleep(1);
								}
								
								
								
								
								
								
								
							}
							
							else if (Operation2 == 4) //Login Exit
							{
								cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
								cout<<"Leaving User Page"<<endl;
								cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
								loginexit=1;
								sleep(1);
								system("cls");
								Operation1=0;
								
							}
						}
						
					}
					else
					{
						cout<<endl<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
						cout<<"Incorrect Password"<<endl;
						cout<<"Returning to Main Panel"<<endl;
						cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl<<endl;
						a=1;
					}	
				}				       	
			}
			if (a == 0)
			{
				cout<<endl<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
				cout<<"User Not Found"<<endl;
				cout<<"Returning to Main Panel"<<endl;
				cout<<"xxxxxxxxxxxxxxxxxxxxxxxxx"<<endl<<endl;
			}					      	 	
		}			 	 	
		
		else if (Operation1 == 2) // New User Panel
		{
			ifstream read;
			read.open("User Info.txt");
			for (i=0; i<U; i++)
			{
				read>>alluserinfo[i].userid;
				read>>alluserinfo[i].password;
				read>>alluserinfo[i].FName;
				read>>alluserinfo[i].LName;
				read>>alluserinfo[i].Age;
				read>>alluserinfo[i].PhoneNum;
				read>>alluserinfo[i].Security_ver;
			}
			read.close();
			
			exit1=0;
			
			cout<<"|___________________________________________________________|"<<endl;
			cout<<"|\t\t   Register New User                        |"<<endl;
			cout<<"|___________________________________________________________|"<<endl;
			cout<<"Enter New User ID     : ";
			cin>>newuser.userid;
			for (i=0; i<U; i++)
			{
				if(newuser.userid == alluserinfo[i].userid)
				{
					exit1 =1;
				}																				
			}
			
			if (exit1 == 1)
			{
				cout<<endl<<"User ID Already Exists, Please Proceed to Login or Forget Password"<<endl<<endl;
			}
			
			if (exit1 == 0)
			{
				cout<<"Enter Password        : ";
				cin>>newuser.password;
				cout<<"Enter First Name      : ";
				cin>>newuser.FName;
				cout<<"Enter Last Name       : ";
				cin>>newuser.LName;
				cout<<"Enter Age             : ";
				cin>>newuser.Age;
				cout<<"Enter Phone Number    : ";
				cin>>newuser.PhoneNum;
				cout<<"Enter Security Phrase : ";
				cin>>newuser.Security_ver;
			
				// Write user information to the file
				ofstream write1;
				write1.open("User Info.txt", ios::app);
				write1<<newuser.userid <<" ";
				write1<<newuser.password <<" ";
				write1<<newuser.FName <<" ";
				write1<<newuser.LName <<" ";
				write1<<newuser.Age <<" ";
				write1<<newuser.PhoneNum <<" ";
				write1<<newuser.Security_ver<<" ";
				write1<<endl; 
					
				write1.close();
				cout <<"User Info successfully saved!!"<<endl<<endl;	
				U++;			
			}
		}
			
		else if (Operation1 == 3) //Forget Password
		{
			// open file in write mode change password
			ifstream read;
			read.open("User Info.txt");
			a=0;
			for (i=0; i<U; i++)
			{
				read>>alluserinfo[i].userid ;
				read>>alluserinfo[i].password;
				read>>alluserinfo[i].FName;
				read>>alluserinfo[i].LName;
				read>>alluserinfo[i].Age;
				read>>alluserinfo[i].PhoneNum;
				read>>alluserinfo[i].Security_ver;
			}
			
			cout<<"|___________________________________________________________|"<<endl;
			cout<<"|\t\t     Changing Password                      |"<<endl;
			cout<<"|___________________________________________________________|"<<endl;
			cout<<"Enter User ID : ";
			cin>>user.userid;
			cout<<"Enter you security phrase : ";
			cin>>user.Security_ver;
				
			for (i=0; i<U; i++)
  			{
  				if(user.userid == alluserinfo[i].userid)
				{
				 	if(user.Security_ver == alluserinfo[i].Security_ver)
				 	{
				 		ofstream write2;
						write2.open("User Info.txt");
				 		cout<<"Enter New Password"<<endl;
				 		cin>>user.password;
				 		
				 		if(user.password == alluserinfo[i].password)
				 		{
				 			cout<<"New Password is the Previous Password"<<endl<<endl;
						}
						
						else
						{
							cout<<"Password successfully changed"<<endl<<endl;
				 			alluserinfo[i].password = user.password;
				 			for (j=0; j<U; j++)
							{
								write2<<alluserinfo[j].userid<<" ";
								write2<<alluserinfo[j].password<<" ";
								write2<<alluserinfo[j].FName<<" ";
								write2<<alluserinfo[j].LName<<" ";
								write2<<alluserinfo[j].Age<<" ";
								write2<<alluserinfo[j].PhoneNum<<" ";
								write2<<alluserinfo[j].Security_ver<<" ";
								write2<<endl;
							}
							write2.close();	
								
						}										 													
					}
					
					else
						cout<<"Security Verification Incorrect"<<endl<<endl;
					a=1;
				}
										       	
			}
			if (a==0)
				cout<<"User Not Found"<<endl<<endl;
		}
		
		else if(Operation1 == 4)
		{
			cout<<"THANKS FOR USING OUR SYSTEM!!!"<<endl;
			mainexit=1;
		}		 
		
		else
			cout<<"Please Enter Valid Operation"<<endl;
	}	
}
