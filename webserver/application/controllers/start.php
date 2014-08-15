<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Start extends CI_Controller {

	public function __construct(){
		parent::__construct();
		$this->load->model('security_m','securitym');
	}
	
	public function index(){
	  $result = $this->securitym->logged();
	  $user = $this->session->userdata('user');
	  $user_id = null;
	  
	  if(!empty($user)){
	    $user_id = $user->user_id;
	  }
	  $result = $this->securitym->logged($user_id);
	  
	  if($result){
		  
		  $this->load->view('home');
	  }else{
		  $this->load->view('welcome_message');
	  }
	
	}
	
	public function formAddTask(){
	  $this->load->view('formAddTask');
	}
	
	public function addTask(){
	  
	  $data['schedule_starts'] = $this->input->post('year_start')."-".$this->input->post('month_start')."-".$this->input->post('day_start');
	  $data['schedule_starts'] .= " ".$this->input->post('hour_start').":".$this->input->post('minute_start');
	  
	  $data['schedule_ends'] = $this->input->post('year_end')."-".$this->input->post('month_end')."-".$this->input->post('day_end');
	  $data['schedule_ends'] .= " ".$this->input->post('hour_end').":".$this->input->post('minute_end');
	  
	  $data['schedule_name'] = $this->input->post('schedule_name');
	  $data['schedule_added'] = time();
	  
	  $user = $this->session->userdata('user');
	  $data['user_id'] = $user->user_id;
	  
	  print_r($data);
	}
}

/* End of file welcome.php */
/* Location: ./application/controllers/welcome.php */
