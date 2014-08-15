<?php
  $mes = array(   1=>'Enero',  2=>'Febrero',    3=>'Marzo',  4=>'Abril',    5=>'Mayo',  6=>'Junio',
    7=>'Julio',  8=>'Agosto',    9=>'Setiembre',  10=>'Octubre',   11=>'Noviembre',  12=>'Diciembre'  );
  ?>
<h3>Agregar Tarea</h3>
<form method="post" action="<?php echo site_url('start/addTask');?>">
  <table>
    <tr>
      <td>Nombre</td>
      <td><input type='text' name='schedule_name'/></td>
    </tr>
    <tr>
      <td>Inicia</td>
      <td>
	  <select name='day_start'>
	  <?php for($i=1;$i<32;$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>/
	  <select name='month_start'>
	  <?php for($i=1;$i<13;$i++) echo "\n<option value='$i'>$mes[$i]</option>"; ?>
	  </select>/
	  <select name='year_start'>
	  <?php for($i=date('Y');$i<(date('Y')+10);$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>
	  <select name='hour_start'>
	  <?php for($i=0;$i<24;$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>:
	  <select name='minute_start'>
	  <?php for($i=0;$i<60;$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>
      </td>
    </tr>
    <tr>
      <td>Finaliza</td>
      <td>
	  <select name='day_end'>
	  <?php for($i=1;$i<32;$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>/
	  <select name='month_end'>
	  <?php for($i=1;$i<13;$i++) echo "\n<option value='$i'>$mes[$i]</option>"; ?>
	  </select>/
	  <select name='year_end'>
	  <?php for($i=date('Y');$i<(date('Y')+10);$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>
	  <select name='hour_end'>
	  <?php for($i=0;$i<24;$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>:
	  <select name='minute_end'>
	  <?php for($i=0;$i<60;$i++) echo "\n<option value='$i'>$i</option>"; ?>
	  </select>
      </td>
    </tr>
    <tr>
      <td><input type='reset' value='Restablecer'/></td>
      <td><input type='submit' value='Agregar'/></td>
    </tr>
  </table>
</form>